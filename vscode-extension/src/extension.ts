import * as fs from 'node:fs';
import * as path from 'node:path';
import * as vscode from 'vscode';
import {
    LanguageClient,
    TransportKind,
    Trace
} from 'vscode-languageclient/node';
import type {
    LanguageClientOptions,
    ServerOptions,
} from 'vscode-languageclient/node';

let client: LanguageClient | undefined;
let outputChannel: vscode.OutputChannel;
let traceOutputChannel: vscode.OutputChannel;
let extensionContext: vscode.ExtensionContext | undefined;

function findServerPath(context: vscode.ExtensionContext): string {
    const config = vscode.workspace.getConfiguration('otterlang');
    let serverPath = config.get<string>('lsp.serverPath', '');
    
    if (!serverPath || serverPath === 'otterlang-lsp') {
        const possiblePaths = [
            path.join(process.env.HOME || '', 'Downloads', 'otterlang', 'target', 'release', 'otterlang-lsp'),
            path.join(process.env.HOME || '', 'Downloads', 'otterlang', 'target', 'debug', 'otterlang-lsp'),
            path.join(context.extensionPath, '..', 'target', 'release', 'otterlang-lsp'),
            path.join(context.extensionPath, '..', 'target', 'debug', 'otterlang-lsp'),
            'otterlang-lsp'
        ];
        
        for (const possiblePath of possiblePaths) {
            try {
                if (fs.existsSync(possiblePath)) {
                    serverPath = possiblePath;
                    break;
                }
            } catch {
            }
        }
        
        if (!serverPath || serverPath === 'otterlang-lsp') {
            vscode.window.showErrorMessage(
                'OtterLang LSP server not found. Please set "otterlang.lsp.serverPath" in settings.'
            );
            serverPath = 'otterlang-lsp';
        }
    }
    
    return serverPath;
}

function createClient(context: vscode.ExtensionContext): LanguageClient {
    const serverPath = findServerPath(context);
    const config = vscode.workspace.getConfiguration('otterlang');
    const traceLevel = config.get<string>('lsp.trace', 'off');
    
    const serverOptions: ServerOptions = {
        run: { command: serverPath, transport: TransportKind.stdio },
        debug: { command: serverPath, transport: TransportKind.stdio }
    };

    const clientOptions: LanguageClientOptions = {
        documentSelector: [{ scheme: 'file', language: 'otterlang' }],
        synchronize: {
            fileEvents: vscode.workspace.createFileSystemWatcher('**/*.ot')
        },
        outputChannel: outputChannel,
        traceOutputChannel: traceOutputChannel
    };

    const languageClient = new LanguageClient(
        'otterlang',
        'OtterLang Language Server',
        serverOptions,
        clientOptions
    );
    
    const trace = traceLevel === 'off' ? Trace.Off : traceLevel === 'messages' ? Trace.Messages : Trace.Verbose;
    languageClient.setTrace(trace);
    
    return languageClient;
}

async function startServer(context: vscode.ExtensionContext): Promise<void> {
    if (client) {
        await client.start();
        vscode.window.showInformationMessage('OtterLang Language Server started');
    } else {
        client = createClient(context);
        await client.start();
        vscode.window.showInformationMessage('OtterLang Language Server started');
    }
}

async function stopServer(): Promise<void> {
    if (client) {
        await client.stop();
        client = undefined;
        vscode.window.showInformationMessage('OtterLang Language Server stopped');
    }
}

async function restartServer(context: vscode.ExtensionContext): Promise<void> {
    if (client) {
        await client.stop();
        client = undefined;
    }
    client = createClient(context);
    await client.start();
    vscode.window.showInformationMessage('OtterLang Language Server restarted');
}

async function toggleLogs(): Promise<void> {
    const config = vscode.workspace.getConfiguration('otterlang');
    const currentTrace = config.get<string>('lsp.trace', 'off');
    const newTrace = currentTrace === 'off' ? 'verbose' : 'off';
    await config.update('lsp.trace', newTrace, vscode.ConfigurationTarget.Global);
    vscode.window.showInformationMessage(`LSP logs ${newTrace === 'off' ? 'disabled' : 'enabled'}`);
    if (client && extensionContext) {
        await restartServer(extensionContext);
    }
}

function showOutput(): void {
    outputChannel.show();
}

export function activate(context: vscode.ExtensionContext) {
    extensionContext = context;
    outputChannel = vscode.window.createOutputChannel('OtterLang');
    traceOutputChannel = vscode.window.createOutputChannel('OtterLang Trace');
    
    client = createClient(context);
    client.start();
    
    context.subscriptions.push(
        vscode.commands.registerCommand('otterlang.restartServer', () => restartServer(context)),
        vscode.commands.registerCommand('otterlang.startServer', () => startServer(context)),
        vscode.commands.registerCommand('otterlang.stopServer', () => stopServer()),
        vscode.commands.registerCommand('otterlang.toggleLogs', () => toggleLogs()),
        vscode.commands.registerCommand('otterlang.showOutput', () => showOutput()),
        outputChannel,
        traceOutputChannel
    );
}

export function deactivate(): Thenable<void> | undefined {
    if (!client) {
        return undefined;
    }
    return client.stop();
}

