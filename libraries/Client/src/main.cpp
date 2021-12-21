#include <client.hpp>
#include <json.hpp>
#include <vector>
struct Response
{
int status_hero;
std::vector<int> stones ;
};

int main() {
Client s;
Response response_;
int n=0;
std::cin >> n;
response_.status_hero = n;
for(int i=0;i<3;i++){
    std::cin>>n;
    response_.stones.push_back(n);
}
nlohmann::json j;

j["list"]=response_.stones;
j["buff"]=response_.status_hero;

std::string ss = j.dump();

s.send_msg(ss);
std::cout <<ss;
}