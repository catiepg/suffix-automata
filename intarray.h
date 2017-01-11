#ifndef ARRAY_H
#define ARRAY_H

const int DEFAULT = -1;

template <const int SIZE>
struct IntArray {
    int* data;
    int idx;
    int size;

    IntArray() {
        this->data = new int[1];
        this->data[0] = DEFAULT;
        this->idx = DEFAULT;
        this->size = 0;
    }

    IntArray(const IntArray &arr) {
        if (arr.size <= 1) {
            this->data = new int[1];
            this->data[0] = arr.data[0];
        } else {
            this->data = new int[SIZE];
            for (int i = 0; i < SIZE; i++) {
                this->data[i] = arr.data[i];
            }
        }

        this->idx = arr.idx;
        this->size = arr.size;
    }

    ~IntArray() {
        delete[] this->data;
    }

    int get(int index) {
        if (this->size == 1 && this->idx == index) return this->data[0];
        if (this->size > 1) return this->data[index];
        return DEFAULT;
    }

    void set(int index, int value) {
        if (this->size == 0) {
            this->idx = index;
            this->size = 1;
            this->data[0] = value;
            return;
        }

        if (this->size == 1) {
            int* newData = new int[SIZE];

            for (int i = 0; i < SIZE; i++) newData[i] = DEFAULT;

            newData[this->idx] = this->data[0];
            delete[] this->data;

            this->data = newData;
            this->idx = DEFAULT;
        }

        this->size++;
        this->data[index] = value;
    }

    int index(int value) {
        if (this->size == 1 && this->data[0] == value) return 0;
        if (this->size > 1) {
            for (int i = 0; i < SIZE; i++) {
                if (this->data[i] == value) return i;
            }
        }
        return DEFAULT;
    }
};

#endif
