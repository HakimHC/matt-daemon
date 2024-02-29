#ifndef SIGNAL_HANDLER_HPP
#define SIGNAL_HANDLER_HPP

class SignalHandler {
    public:
        static void sigListen();
        static void handler(int);
    private:
        SignalHandler();
        ~SignalHandler();
        SignalHandler(const SignalHandler&);
        SignalHandler& operator=(const SignalHandler&);
};

#endif // SIGNAL_HANDLER_HPP
