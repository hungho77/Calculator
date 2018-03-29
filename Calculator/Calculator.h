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
	enum class ActionType : char { Number, Plus, Minus, Multi, Div, Equal, None, And, Or, Xor, Not };
	struct Action
	{
		ActionType actionType;
		QInt value;
	};

	void reset();
	bool addInput(const Action& input);
	Action getLastInput() const;
	// Current (partial) result as much as it can be calculated. Terms results are not
	// taken into account until the term has finished: 3 + 2 X 5 would return 3 becouse
	// the term calculation is not finished.
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
	std::vector<Action> m_actions; // all the actions user has inputted (see ActionType)
								   // m_leftExpression is always the left hand side of the expression. An example:
								   // 5 -> m_leftExpression = ActionType::None (reset) (*)
								   // 5 + 3 + -> m_leftExpression = 8
								   // 5 + 3 + 1 = -> m_leftExpression = 9
								   // 5 + 3 + 1 = 9 + -> m_leftExpression = 9 (here after "=" the user 
								   // of this class must add 9 before using "+" becouse "=" "resets" 
								   // the calculations and they must
								   // start from the beginning, meaning a number is entered first).
								   // 5 + 3 + 1 = 9 x -> m_leftExpression = ActionType::None (reset)
								   // So "=" and "None" (see (*)) are the beginning of the calculations.
	LeftExpression m_leftExpression;
	// if the calculation starts ("=" is also a start) with terms:
	// 3 x 4, this will go into m_leftTerm (not into m_leftExpression). So m_leftExpression
	// stays zero until next expression comes.
	// 5 + 3 + 1 = 9 x -> m_leftTerm = 9 (m_leftExpression = ActionType::None)
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

