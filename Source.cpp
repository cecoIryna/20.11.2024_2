#include <iostream>
using namespace std;

class IOutput
{
public:
    virtual void Show() const = 0;
    virtual void Show(string info) const = 0;
    virtual ~IOutput() {}
};

struct IMath
{
    virtual int Max() const = 0;
    virtual int Min() const = 0;
    virtual float Avg() const = 0;
    virtual bool Search(int v) const = 0;
    virtual ~IMath() {}
};

struct ISort
{
    virtual void SortAsc() = 0;
    virtual void SortDesc() = 0;
    virtual void SortByParam(bool isAsc) = 0;
    virtual ~ISort() {}
};

class Array : public IOutput, public IMath, public ISort
{
private:
    int* data; 
    int size;

public:
    Array(int size) : size(size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0; 
        }
    }

    ~Array() {
        delete[] data;
    }

    void Fill(int* values, int count) {
        for (int i = 0; i < size && i < count; i++) {
            data[i] = values[i];
        }
    }

    void Show() const {
        cout << "Array elements: ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void Show(string info) const {
        cout << info << endl;
        Show();
    }

    int Max() const override {
        int maxVal = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > maxVal) {
                maxVal = data[i];
            }
        }
        return maxVal;
    }

    int Min() const override {
        int minVal = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] < minVal) {
                minVal = data[i];
            }
        }
        return minVal;
    }

    float Avg() const override {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += data[i];
        }
        return static_cast<float>(sum) / size;
    }

    bool Search(int v) const override {
        for (int i = 0; i < size; i++) {
            if (data[i] == v) {
                return true;
            }
        }
        return false;
    }

    void SortAsc() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    void SortDesc() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (data[j] < data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    void SortByParam(bool isAsc) {
        if (isAsc) {
            SortAsc();
        }
        else {
            SortDesc();
        }
    }

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
};

int main() {
    Array arr(5);

    int values[] = { 3, 1, 4, 1, 5 };
    arr.Fill(values, 5);

    cout << "Testing IOutput:" << endl;
    arr.Show();
    arr.Show("Array elements with info:");

    cout << "\nTesting IMath:" << endl;
    cout << "Max: " << arr.Max() << endl;
    cout << "Min: " << arr.Min() << endl;
    cout << "Average: " << arr.Avg() << endl;
    cout << "Search for 4: " << (arr.Search(4) ? "Found" : "Not found") << endl;
    cout << "Search for 10: " << (arr.Search(10) ? "Found" : "Not found") << endl;

    cout << "\nTesting ISort:" << endl;
    cout << "Original array:" << endl;
    arr.Show();

    cout << "Array sorted ascending:" << endl;
    arr.SortAsc();
    arr.Show();

    cout << "Array sorted descending:" << endl;
    arr.SortDesc();
    arr.Show();

    cout << "Array sorted by parameter (ascending):" << endl;
    arr.SortByParam(true);
    arr.Show();

    cout << "Array sorted by parameter (descending):" << endl;
    arr.SortByParam(false);
    arr.Show();
    return 0;
}