#include <string>

class Trace {
    public:
        Trace();
        ~Trace();
        
        std::string GenerateTraceId();
        
    private:
        std::string trace_id;
};
