
#include<iostream>
#include<vector>


std::vector<float> convert(float x, float y, float max=5.0) {
    x = (2.0f * x / max) - 1.0f;
    y = (2.0f * y / max) - 1.0f;
    return { x, y };
}
void points()
{
   std::vector<std::vector<float>> v;
   v.push_back(convert(1.6, 2.5));
   v.push_back(convert(1.2, 1.5));
   v.push_back(convert(2.0, 1.5));
   v.push_back(convert(0.0, 1.5));
   v.push_back(convert(3.0, 1.5));
   v.push_back(convert(1.0, 1.0));
   v.push_back(convert(2.0, 1.0));
   v.push_back(convert(0.6, 0.0));
   v.push_back(convert(2.2, 0.0));
   v.push_back(convert(1.6, 0.5));

   for(auto i : v){
      std::cout << i[0] << ", "<< i[1];
      std::cout << "\n";
   }
}
int main()
{
   points();
   std::cin.get();
}
