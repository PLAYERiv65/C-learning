#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0));  // 使用当前时间作为随机数生成器的种子
    std::ofstream fout("input.txt");  // 创建一个输出文件流

    int num_elements = 10000;  // 生成的元素数量
    for(int i = 0; i < num_elements; i++) {
        fout << std::rand() % 10000 << std::endl;  // 生成一个0到9999之间的随机整数
    }

    fout.close();  // 关闭文件流
    return 0;
}