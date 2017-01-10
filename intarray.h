#ifndef ARRAY_H
#define ARRAY_H

const int DEFAULT = -1;

template <const int SIZE>
struct IntArray {
    int* data;
    int index;
    int size;

    IntArray() {
        this->data = new int[1];
        this->data[0] = DEFAULT;
        this->index = DEFAULT;
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

        this->index = arr.index;
        this->size = arr.size;
    }

    ~IntArray() {
        delete[] this->data;
    }

    const int operator[](int index) const {
        if (this->size == 1 && this->index == index) return this->data[0];
        if (this->size > 1) return this->data[index];
        return DEFAULT;
    }

    int& operator[](const int index) {
        if (this->size == 0) {
            this->index = index;
            this->size = 1;
            return this->data[0];
        }

        if (this->size == 1) {
            int* newData = new int[SIZE];

            for (int i = 0; i < SIZE; i++) newData[i] = DEFAULT;

            newData[this->index] = this->data[0];
            delete[] this->data;

            this->data = newData;
            this->index = DEFAULT;
        }

        this->size++;
        return this->data[index];
    }

    int getIndex(int value) {
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
