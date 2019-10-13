#include <string>

class TraceIdHolder {

public:
    void set(std::string trace_id);
    std::string get();

private:
    std::string trace_id;

};