#ifndef DAEMONIZER_HPP
#define DAEMONIZER_HPP

class Daemonizer {
    public:
        static int daemonize();
    private:
        Daemonizer();
        ~Daemonizer();
        Daemonizer(const Daemonizer&);
        Daemonizer& operator=(const Daemonizer&);

        static void _closeAndRedirectFds();

};

#endif // DAEMONIZER_HPP