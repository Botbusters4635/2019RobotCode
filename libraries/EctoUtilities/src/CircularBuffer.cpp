//
// Created by Abiel on 9/8/18.
//

#include "EctoUtilities/CircularBuffer.h"

template<class T>
CircularBuffer<T>::CircularBuffer(std::size_t bufferSize) {
	this->bufferSize = bufferSize;
}

template<class T>
T CircularBuffer<T>::getFirstElement() const {
	return *data.begin();
}

template<class T>
T CircularBuffer<T>::getLastElement() const {
	return *(--data.end());
}

template<class T>
void CircularBuffer<T>::addElement(const T &element) {
	if (data.size() + 1 > bufferSize)
		data.pop_front();

	data.push_back(element);
}

template<class T>
void CircularBuffer<T>::setBufferSize(std::size_t size) {
	this->bufferSize = size;

	while (data.size() > bufferSize)
		data.pop_front();
}

template<class T>
std::size_t CircularBuffer<T>::getBufferSize() const {
	return bufferSize;
}

template<class T>
std::list<T> CircularBuffer<T>::getBuffer() const {
	return data;
}

template<class T>
void CircularBuffer<T>::eraseBuffer() {
	data.clear();
}

template<class T>
bool CircularBuffer<T>::isEmpty() const {
	return data.empty();
}