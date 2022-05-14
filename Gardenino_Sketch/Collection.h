#pragma once

#define COLLECTION_SIZE 10

template <typename T>
class Collection
{
public:
	Collection() : ElementsCount(0)
	{
	}

	void AddElement(T* element)
	{
		if (ElementsCount + 1 >= COLLECTION_SIZE)
		{
			return;
		}

		Elements[ElementsCount] = element;
		ElementsCount++;
	}

	T* GetElement(int index)
	{
		if (index < 0 || index >= ElementsCount)
		{
			return nullptr;
		}

		return Elements[index];
	}

	void RemoveElement(int index)
	{
		if (index < 0 || index >= ElementsCount)
		{
			return;
		}

		for (int i = index; i < ElementsCount - 1; i++)
		{
			Elements[i] = Elements[i + 1];
		}
		ElementsCount--;
	}

	int GetElementsCount() const
	{
		return ElementsCount;
	}

private:
	T* Elements[COLLECTION_SIZE];
	int ElementsCount;
};
