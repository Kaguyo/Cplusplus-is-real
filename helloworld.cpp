#include <iostream>
#include <vector>

typedef std::vector<std::pair<std::string, int>> pairlist_t;

namespace first {
    int x = 50;
    std::string vegetaName = "Vegeta";
}
namespace secondUniverse {
    std::string vegetaName = "Vegeta Alt";
}
int main(){
    using namespace secondUniverse;
//  using namespace std  => alternative to not precede std statements with std::
//  !!   std has over 100 entities or so, def gonna conflict in bigger programs.
    const int X = 10;
    int y;
    y = 10;
    const int Z = y + first::x;
    std::string name = "Goku";
    
    

    std::cout << "Hello world!" << std::endl; // Equals to \n+ flushing !!!!! 
    std::cout << "It's time to learn C++" << std::endl;
    std::cout << X << '\n' << X << std::endl;
    std::cout << name << '\n';
    std::cout << Z << '\n';
    std::cout << vegetaName;

    return 0;
}