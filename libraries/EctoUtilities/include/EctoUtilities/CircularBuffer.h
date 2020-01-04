//
// Created by Abiel on 9/8/18.
//

#ifndef BOTBUSTERSREBIRTH_CIRCULARBUFFER_H
#define BOTBUSTERSREBIRTH_CIRCULARBUFFER_H

#include <list>

template<class T>
class CircularBuffer {
public:
	explicit CircularBuffer<T>(std::size_t bufferSize);

	T getFirstElement() const;

	T getLastElement() const;

	void addElement(const T &element);

	void setBufferSize(std::size_t size);

	std::size_t getBufferSize() const;

	std::list<T> getBuffer() const;

	bool isEmpty() const;

	void eraseBuffer();

private:
	std::list<T> data;
	std::size_t bufferSize;
};


#endif //BOTBUSTERSREBIRTH_CIRCULARBUFFER_H
