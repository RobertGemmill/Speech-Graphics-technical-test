#include <iostream>
#include <string>
using namespace std;

template <typename TOptionalValue> class OptionalValue
{

private:
	TOptionalValue Value;
	bool bIsNotEmpty = false;

public:
	TOptionalValue& GetValue()
	{
		return Value;
	}

	const TOptionalValue& GetValue() const
	{
		return Value;
	}

	void SetValue(const TOptionalValue& v)
	{
		Value = v;
		bIsNotEmpty = true;
	}

	bool CheckValue() const
	{
		return bIsNotEmpty;
	}

	operator bool() const
	{
		return bIsNotEmpty;
	}

	void ClearValue()
	{
		bIsNotEmpty = false;
	}
};

int main()
{
	OptionalValue<int> Ioptional;
	OptionalValue<float> Foptional;
	Ioptional.SetValue(5);
	Foptional.SetValue(7.5f);
	Foptional.ClearValue();
	if (Ioptional)
	{
		cout << "Value is: ";
		cout << Ioptional.GetValue() <<endl;
	}
	else
	{
		cout << "Value Empty" << endl;
	}
	if (Foptional)
	{
		cout << "Value is: ";
		cout << Foptional.GetValue() << endl;
	}
	else
	{
		cout << "Value Empty" << endl;
	}
}
