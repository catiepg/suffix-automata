#ifndef ARRAY_H
#define ARRAY_H

const int NONE = -1;

template <class T, const T& DEFAULT, const int SIZE>
struct Array {
    T* data;
    int index;
    int size;

    Array() {
        this->data = new T[1];
        this->data[0] = DEFAULT;
        this->index = NONE;
        this->size = 0;
    }

    Array(const Array &arr) {
        if (arr.size <= 1) {
            this->data = new T[1];
            this->data[0] = arr.data[0];
        } else {
            this->data = new T[SIZE];
            for (int i = 0; i < SIZE; i++) {
                this->data[i] = arr.data[i];
            }
        }

        this->index = arr.index;
        this->size = arr.size;
    }

    ~Array() {
        delete[] this->data;
    }

    const T operator[](int index) const {
        if (this->size == 1 && this->index == index) return this->data[0];
        if (this->size > 1) return this->data[index];
        return DEFAULT;
    }

    T& operator[](const int index) {
        if (this->size == 0) {
            this->index = index;
            this->size = 1;
            return this->data[0];
        }

        if (this->size == 1) {
            T* newData = new T[SIZE];

            for (int i = 0; i < SIZE; i++) {
                newData[i] = DEFAULT;
            }

            newData[this->index] = this->data[0];
            delete[] this->data;
            this->data = newData;
            this->index = NONE;
        }

        this->size++;
        return this->data[index];
    }

    int getIndex(T value) {
        if (this->size == 1 && this->data[0] == value) return 0;
        if (this->size > 1) {
            for (int i = 0; i < SIZE; i++) {
                if (this->data[i] == value) return i;
            }
        }
        return NONE;
    }
};

#endif
