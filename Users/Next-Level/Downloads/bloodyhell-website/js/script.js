// BloodyHell Industries Website JavaScript
// Classic 2007-era interactive features

document.addEventListener('DOMContentLoaded', function() {
    // Smooth scrolling for navigation links
    const navLinks = document.querySelectorAll('a[href^="#"]');
    
    navLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault();
            
            const targetId = this.getAttribute('href');
            const targetSection = document.querySelector(targetId);
            
            if (targetSection) {
                targetSection.scrollIntoView({
                    behavior: 'smooth',
                    block: 'start'
                });
                
                // Update active navigation state
                updateActiveNav(this);
            }
        });
    });
    
    // Active navigation highlighting
    function updateActiveNav(activeLink) {
        // Remove active class from all nav links
        document.querySelectorAll('#header .nav a, .nav-sidebar a').forEach(link => {
            link.classList.remove('active');
        });
        
        // Add active class to clicked link
        activeLink.classList.add('active');
    }
    
    // Scroll spy for automatic nav highlighting
    function handleScrollSpy() {
        const sections = document.querySelectorAll('section[id]');
        const scrollPos = window.scrollY + 100;
        
        sections.forEach(section => {
            const sectionTop = section.offsetTop;
            const sectionHeight = section.offsetHeight;
            const sectionId = section.getAttribute('id');
            const correspondingNav = document.querySelector(`#header .nav a[href="#${sectionId}"], .nav-sidebar a[href="#${sectionId}"]`);
            
            if (scrollPos >= sectionTop && scrollPos < sectionTop + sectionHeight) {
                // Remove active from all
                document.querySelectorAll('#header .nav a, .nav-sidebar a').forEach(link => {
                    link.classList.remove('active');
                });
                
                // Add active to corresponding nav
                if (correspondingNav) {
                    correspondingNav.classList.add('active');
                }
            }
        });
    }
    
    // Add scroll event listener for scroll spy
    window.addEventListener('scroll', handleScrollSpy);
    
    // Button hover effects (classic 2007-style)
    const buttons = document.querySelectorAll('.btn');
    
    buttons.forEach(button => {
        button.addEventListener('mouseenter', function() {
            this.style.transform = 'translateY(-1px)';
        });
        
        button.addEventListener('mouseleave', function() {
            this.style.transform = 'translateY(0)';
        });
    });
    
    // Project track highlighting on hover
    const projectTracks = document.querySelectorAll('.project-track');
    
    projectTracks.forEach(track => {
        track.addEventListener('mouseenter', function() {
            this.style.backgroundColor = '#f9f9f9';
            this.style.borderColor = '#4A90D9';
        });
        
        track.addEventListener('mouseleave', function() {
            this.style.backgroundColor = '';
            this.style.borderColor = '';
        });
    });
    
    // Statistics counter animation (simple version)
    function animateStats() {
        const stats = document.querySelectorAll('.stat-item strong');
        stats.forEach(stat => {
            const text = stat.textContent;
            if (text === 'Founded') {
                stat.style.color = '#D97B2E';
            } else if (text === 'Philosophy') {
                stat.style.color = '#2E5C8A';
            } else if (text === 'Focus') {
                stat.style.color = '#4A90D9';
            }
        });
    }
    
    // Initialize stats animation
    animateStats();
    
    // Add loading state for images
    const images = document.querySelectorAll('img');
    images.forEach(img => {
        img.addEventListener('load', function() {
            this.style.opacity = '0';
            this.style.transition = 'opacity 0.3s ease-in-out';
            setTimeout(() => {
                this.style.opacity = '1';
            }, 50);
        });
    });
    
    // Console message for classic 2007 feel
    console.log('BloodyHell Industries INC - Open Source Software Since 2007');
    console.log('Everyone deserves a software');
    
    // Simple browser compatibility check
    if (!document.querySelector) {
        console.warn('This site is optimized for modern browsers. Please update for the best experience.');
    }
});

// Classic 2007-style utility functions
function addClassicEffect(element) {
    // Add subtle shadow on hover (classic web 2.0 effect)
    element.addEventListener('mouseenter', function() {
        this.style.boxShadow = '0 3px 8px rgba(0, 0, 0, 0.2)';
    });
    
    element.addEventListener('mouseleave', function() {
        this.style.boxShadow = '';
    });
}

// Apply classic effects to key elements
document.addEventListener('DOMContentLoaded', function() {
    const boxes = document.querySelectorAll('.box, .content-box');
    boxes.forEach(box => addClassicEffect(box));
});

// Add some 2007-era flair
function addRetroFlair() {
    // Add subtle rotation to some elements (very subtle, like 2007 sites)
    const hero = document.querySelector('.hero');
    if (hero) {
        hero.style.transform = 'rotate(0.01deg)'; // Slight rotation for that 2007 feel
    }
}

// Initialize retro effects
document.addEventListener('DOMContentLoaded', addRetroFlair);