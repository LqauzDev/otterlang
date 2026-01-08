#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Test framework
static int tests_run = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s - %s\n", __func__, message); \
            return 0; \
        } \
    } while(0)

#define RUN_TEST(test_func) \
    do { \
        printf("Running %s...\n", #test_func); \
        tests_run++; \
        if (test_func()) { \
            printf("PASS: %s\n\n", #test_func); \
            tests_passed++; \
        } else { \
            tests_failed++; \
        } \
    } while(0)

// Forward declarations for test functions
int test_context(void);
int test_module(void);
int test_types(void);
int test_values(void);
int test_function(void);
int test_basic_block(void);
int test_builder(void);
int test_instructions(void);
int test_analysis(void);
int test_transforms(void);
int test_serialization(void);
int test_utils(void);

int main() {
    printf("=== GeekIR Test Suite ===\n\n");
    
    // Run all tests
    RUN_TEST(test_context);
    RUN_TEST(test_types);
    RUN_TEST(test_values);
    RUN_TEST(test_module);
    RUN_TEST(test_function);
    RUN_TEST(test_basic_block);
    RUN_TEST(test_builder);
    RUN_TEST(test_instructions);
    RUN_TEST(test_analysis);
    RUN_TEST(test_transforms);
    RUN_TEST(test_serialization);
    RUN_TEST(test_utils);
    
    // Print summary
    printf("=== Test Summary ===\n");
    printf("Total tests: %d\n", tests_run);
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    printf("Success rate: %.1f%%\n", tests_run > 0 ? (100.0 * tests_passed / tests_run) : 0.0);
    
    return tests_failed > 0 ? 1 : 0;
}
