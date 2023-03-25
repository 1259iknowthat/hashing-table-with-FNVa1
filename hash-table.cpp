#include <iostream>
#include <vector>

using namespace std;

const int TABLE_SIZE_M = 100000;
vector<pair<unsigned int, int>> table(TABLE_SIZE_M, make_pair(0, -1));

class FNV1a_Hash{
    private:
        string key;
        const int FNV_PRIME = 16777619;
        const int OFFSET_BASIS = 2166136261;
        unsigned int value;

    public:
        unsigned int hashingFunc(string key) {
            unsigned int hash = OFFSET_BASIS;
            for (char c : key) {
                hash ^= static_cast<unsigned int>(c); // xor with every elements in binary string
                hash *= FNV_PRIME;
            }
            return hash;
        }

        void insertValue(string key){
            this->value = hashingFunc(key);
            unsigned int index = value % TABLE_SIZE_M;
            // handle collision
            while (table[index].second != -1) {
                index = (index + 1) % TABLE_SIZE_M;
            }
            table[index].first = this->value;
            table[index].second = 10; // signature for detecting collision
        }

        void getValue(string key){
            this->value = hashingFunc(key);
            unsigned int index = value % TABLE_SIZE_M;
            while (table[index].second != -1 && table[index].first != value) {
                index = (index + 1) % TABLE_SIZE_M;
            }
            value = table[index].first;
            if (value <= 0) {
                puts("Key not found!");
            } else {
                printf("Hash value: %u\n", this->value);
                printf("Index in table: %u\n", index);
            }
        }

        FNV1a_Hash(){};
        FNV1a_Hash(string key){
            this->key = key;
            this->insertValue(this->key);
            this->getValue(this->key);
        };
};


int main() {
    FNV1a_Hash hashing("1111101");
    hashing.insertValue("110010110010110010110010110010110010110010");
    hashing.getValue("110010");
    hashing.getValue("110010110010110010110010110010110010110010");
    hashing.getValue("001011");
    return 0;
}
