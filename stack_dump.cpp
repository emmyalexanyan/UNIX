#include <iostream>
#include <sstream>
#include <vector>
#include <execinfo.h>
#include <cxxabi.h>

void stack_dump(int depth, std::ostream& stream) {
    if (depth <= 0) return;
    
    void* buffer[depth + 1];
    int nptrs = backtrace(buffer, depth + 1);
    
    if (nptrs <= 1) return;
    char** symbols = backtrace_symbols(buffer, nptrs);

        
    for (int i = 1; i < nptrs; ++i) 
    {
        std::string symbol(symbols[i]);
        size_t begin = symbol.find('(');
        size_t end = symbol.find('+', begin);
        
        if (begin != std::string::npos && end != std::string::npos) 
        {
            std::string mangled = symbol.substr(begin + 1, end - begin - 1);
            int status;
            char* demangled = abi::__cxa_demangle(mangled.c_str(), nullptr, nullptr, &status);
            if (status == 0 && demangled) 
            {
                stream << i << " " << demangled << "\n";
                free(demangled);
            } 
            else
            {
                stream<< i << " " << mangled << " FAIL\n";
            }
        }
        else 
        {
            stream<< i << " " << symbols[i] << "\n";
        }
    }
    
    free(symbols);
}


int main(){
    stack_dump(10,std::cout);
    return 0;

}
