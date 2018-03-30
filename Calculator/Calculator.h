#pragma once
#include <vector>
#include <exception>
#include"QInt.h"

class CalculatorException : public std::exception
{
public:
	enum class ExceptionType : char { None = 0, DividedByZero };
	CalculatorException(std::string textWhat, ExceptionType exceptionType) :
		m_textWhat(textWhat), m_exceptionType(exceptionType)
	{
	}
	virtual const char* what() const throw()
	{
		return m_textWhat.c_str();
	}
private:
	std::string m_textWhat;
	ExceptionType m_exceptionType{ ExceptionType::None };
};

class Calculator
{
public:
	//
	enum Mode : char { Dec, Hex, Bin };
	Mode mode;
	// ActionType: what has been entered from the calculator
	enum class ActionType : char { Number, Plus, Minus, Multi, Div, Equal, None, And, Or, Xor, Not, Lsh, Rsh };
	struct Action
	{
		ActionType actionType;
		QInt value;
	};

	void reset();
	bool addInput(const Action& input);
	Action getLastInput() const;
	QInt getCurrentResult() const;
	bool hasLeftTermValue() const { return m_leftTerm.hasValue(); }
	bool hasLeftExpressionValue() const { return m_leftExpression.hasValue(); }
	bool isOperation(ActionType action) const;
	// actions
	int getActionsSize() { return static_cast<int>(m_actions.size()); }
	const Action& getAction(int i) { return m_actions.at(i); }
private:
	bool isTerm(ActionType action) const;
	bool isExpression(ActionType action) const;
	ActionType getLastOperation();

	// classes:
	// like: +,-
	class LeftExpression
	{
	public:
		void reset();
		void set(QInt value);
		void add(QInt value);
		void and(QInt value);
		void or (QInt value);
		void xor(QInt value);
		void not();
		void lsh(int n);
		void rsh(int n);
		QInt getValue() const { return m_value; }
		bool hasValue() const { return m_hasValue; }
	private:
		bool m_hasValue = false;
		QInt m_value = 0;
	};
	// like: x,/
	class LeftTerm
	{
	public:
		void reset();
		void set(QInt value);
		void multiBy(QInt value);
		QInt getValue() const { return m_value; }
		bool hasValue() const { return m_hasValue; }
	private:
		bool m_hasValue = false;
		QInt m_value = 0;
	};

	// Data members:
	std::vector<Action> m_actions; 						   
	LeftExpression m_leftExpression;
	LeftTerm m_leftTerm;
};

inline void Calculator::LeftExpression::reset()
{
	m_hasValue = false;
	m_value = 0;
}

inline void Calculator::LeftExpression::set(QInt value)
{
	m_hasValue = true;
	m_value = value;
}

inline void Calculator::LeftExpression::add(QInt value)
{
	set(m_value + value);
}

inline void Calculator::LeftExpression::and (QInt value)
{
	set(m_value&value);
}

inline void Calculator::LeftExpression:: or (QInt value)
{
	set(m_value|value);
}

inline void Calculator::LeftExpression:: xor (QInt value)
{
	set(m_value ^ value);
}

inline void Calculator::LeftExpression::not()
{
	set(~m_value);
}

inline void Calculator::LeftExpression::lsh(int n)
{
	set(m_value << n);
}

inline void Calculator::LeftExpression::rsh(int n)
{
	set(m_value >> n);
}

inline void Calculator::LeftTerm::reset()
{
	m_hasValue = false;
	m_value = 0;
}

inline void Calculator::LeftTerm::set(QInt value)
{
	m_hasValue = true;
	m_value = value;
}

inline void Calculator::LeftTerm::multiBy(QInt value)
{
	set(m_value * value);
}

