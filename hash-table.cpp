#include <iostream>
#include <vector>

using namespace std;

const int TABLE_SIZE = 100000;
vector<pair<unsigned int, int>> table(TABLE_SIZE, make_pair(0, -1));

class FNV1a_Hash{
    private:
        string key;
        const int FNV_PRIME = 16777619;
        const int OFFSET_BASIS = 2166136261;

    public:
        unsigned int hashingFunc(string key) {
            unsigned int hash = OFFSET_BASIS;
            for (char c : key) {
                hash ^= static_cast<unsigned int>(c);
                hash *= FNV_PRIME;
            }
            return hash;
        }

        void insertValue(string key){
            unsigned int value = hashingFunc(key);
            int index = 0 % TABLE_SIZE;
            // handle collision
            while (table[index].second != -1) {
                index = (index + 1) % TABLE_SIZE;
            }
            table[index].first = value;
            table[index].second = 10; // signature for detecting collision
        }

        void getValue(string key){
            unsigned int value = hashingFunc(key);
            int index = 0 % TABLE_SIZE;
            while (table[index].second != -1 && table[index].first != value) {
                index = (index + 1) % TABLE_SIZE;
            }
            value = table[index].first;
            if (value <= 0) {
                cout << "Key not found!" << endl;
            } else {
                printf("Hash value: %u\n", value);
                printf("Index in table: %u\n", index);
            }
        }

        FNV1a_Hash(){
            this->key = "00000000";
        };
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
