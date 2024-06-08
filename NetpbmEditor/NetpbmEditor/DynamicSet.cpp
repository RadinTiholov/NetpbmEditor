#include "DynamicSet.h"

DynamicSet::DynamicSet(unsigned N)
{
	bucketsCount = N / elementsInBucket + 1;
	buckets = new uint8_t[bucketsCount]{ 0 };
	this->N = N;
}

DynamicSet::DynamicSet()
{
	this->N = 0;
	bucketsCount = 0;
	buckets = nullptr;
}

void DynamicSet::free()
{
	delete[] buckets;//!!!
	bucketsCount = 0;
	buckets = nullptr;
}
void DynamicSet::copyFrom(const DynamicSet& other)
{
	buckets = new uint8_t[other.bucketsCount];
	for (size_t i = 0; i < other.bucketsCount; i++)
		buckets[i] = other.buckets[i];
	bucketsCount = other.bucketsCount;
	N = other.N;
}

DynamicSet::DynamicSet(const DynamicSet& other)
{
	copyFrom(other);
}
DynamicSet& DynamicSet::operator=(const DynamicSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
DynamicSet::~DynamicSet()
{
	free();
}

unsigned DynamicSet::getBucketIndex(unsigned num) const
{
	return num / elementsInBucket;
}

void DynamicSet::add(unsigned num)
{
	if (num > N)
		return;

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = 1 << bitIndex;
	buckets[bucketIndex] |= mask;

}

void DynamicSet::remove(unsigned num)
{

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = ~(1 << bitIndex);
	buckets[bucketIndex] &= mask;
}

bool DynamicSet::contains(unsigned num) const
{
	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = 1 << bitIndex;

	return buckets[bucketIndex] & mask;
}

void DynamicSet::serializeToAscii(std::ofstream& ofs) const
{
	if (!ofs.is_open())
	{
		throw std::runtime_error(Constants::COULD_NOT_OPEN_FILE_ERROR_MESSAGE);
	}
	for (int i = 0; i <= N; i++)
	{
		if (contains(i)) 
		{
			ofs << 1;
		}
		else
		{
			ofs << 0;
		}
	}
}

void DynamicSet::print() const
{
	std::cout << '{';
	for (int i = 0; i <= N; i++)
	{
		if (contains(i))
			std::cout << i << " ";
	}

	std::cout << '}' << std::endl;
}