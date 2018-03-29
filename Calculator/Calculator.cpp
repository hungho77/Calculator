#include "stdafx.h"
#include "Calculator.h"

Calculator::Action Calculator::getLastInput() const
{
	return m_actions.size() <= 0 ? Action{ ActionType::None, 0 } : m_actions.back();
}

void Calculator::reset()
{
	m_leftExpression.reset();
	m_leftTerm.reset();
	m_actions.clear();
}

bool Calculator::isOperation(ActionType action) const
{
	return (action == ActionType::Plus || action == ActionType::Minus ||
		action == ActionType::Multi || action == ActionType::Div ||
		action == ActionType::Equal || action == ActionType::And || 
		action == ActionType::Or || action == ActionType::Xor || action == ActionType::Not);
}

bool Calculator::isTerm(ActionType action) const
{
	return (action == ActionType::Multi || action == ActionType::Div);
}

bool Calculator::isExpression(ActionType action) const
{
	return (action == ActionType::Plus || action == ActionType::Minus ||
		action == ActionType::And || action == ActionType::Or || action == ActionType::Xor || action == ActionType::Not);
}

Calculator::ActionType Calculator::getLastOperation()
{
	for (auto op = m_actions.rbegin(); op != m_actions.rend(); ++op)
	{
		if (isOperation(op->actionType))
			return op->actionType;
	}
	return ActionType::None;
}

QInt Calculator::getCurrentResult() const
{
	// If "+" or "-" has been entered then this function always returns the current 
	// m_leftExpression value.
	// After "=" m_leftExpression contains the current result. If after "=" a term
	// is pressed (and no expression is pressed) then m_leftExpression is reset and
	// m_leftTerm contains the current result.
	return m_leftExpression.hasValue() ? m_leftExpression.getValue() : m_leftTerm.getValue();
}

// Logic: 
// - If it is a number then just add it to the actions vector (but adding two
// times a number is not allowed as "3 4 6 =" is not a correct syntax. "3 + 6 =" would be correct.)
// - If it is an expression-operation (like "3+4-") then do the operation with the operation before that
// ("3+4" in the example) and add it to "left expression" (m_leftExpression).
// - If it is a term-operation (like 3+4x) add the left number (3) to m_leftExpression and
// the right handside number (4) of the expression operation to m_leftTerm.
// - "=" and "None" as an operation means that a totally new calculation started from there,
// meaning that the first number after them are just assigned to "left expression" (m_leftExpression).
// After "=" and "None" the first temporary results (untill the next expression operator)
// go to m_leftTerm and m_leftExpression remains zero.
// return value: Returns true if input was valid otherwise false
bool Calculator::addInput(const Action& input)
{
	const Calculator::Action lastInput = getLastInput();

	if (input.actionType == ActionType::Number)
	{
		// adding a number after a number would be an error -> that entry is ignored
		if (lastInput.actionType != ActionType::Number)
			m_actions.push_back(input);
	}
	else if (isOperation(input.actionType))
	{
		if (lastInput.actionType == ActionType::Number )
		{
			ActionType lastOperation = getLastOperation();
			switch (lastOperation)
			{
			case ActionType::Plus:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{
					// "3 + 4 -", "3 + 4 ="
					m_leftExpression.add(lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{
					// "3 + 4 x",
					m_leftTerm.set(lastInput.value);
				}
				break;
			case ActionType::Minus:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{
					// "3 - 4 -", "3 - 4 ="
					m_leftExpression.add(-lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{
					// "3 - 4 x",
					m_leftTerm.set(-lastInput.value);
				}
				break;
			case ActionType::Multi:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{
					// "3 x 4 +", "3 x 4 ="
					m_leftExpression.add(m_leftTerm.getValue() * lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType)) // "3 x 4 x"
					m_leftTerm.multiBy(lastInput.value);
				break;
			case ActionType::Div:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{
					if (lastInput.value == 0)
					{
						CalculatorException divByZeroException("Error: Cannot Div By Zero",
							CalculatorException::ExceptionType::DividedByZero);
						throw divByZeroException;
					}
					else
					{
						// "3 / 4 +", "3 / 4 ="
						m_leftExpression.add(m_leftTerm.getValue() / lastInput.value);
						m_leftTerm.reset();
					}
				}
				else if (isTerm(input.actionType)) // "3 / 4 x"
					m_leftTerm.multiBy(1 / lastInput.value);
				break;
			case ActionType::Equal: // "=" is the start of a new beginnning, see (h: *)
				if (isTerm(input.actionType))
				{
					// "= 3 x "
					m_leftExpression.reset();
					m_leftTerm.set(lastInput.value);
				}
				else if (isExpression(input.actionType))
				{
					// "= 3 + "
					m_leftExpression.set(lastInput.value);
					m_leftTerm.reset();
				}
				break;
			case ActionType::None: // "None" is the start of a new beginnning, see (h: *)
				if (isTerm(input.actionType))
				{
					// "3 x "
					m_leftExpression.reset();
					m_leftTerm.set(lastInput.value);
				}
				else if (isExpression(input.actionType))
				{
					// "3 + "
					m_leftExpression.set(lastInput.value);
					m_leftTerm.reset();
				}
				else if(input.actionType == ActionType::Equal)
				{
					m_leftExpression.set(lastInput.value);
					m_leftTerm.reset();
				}
				break;
			case ActionType::And:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{
					
					m_leftExpression.and(lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{
				
					m_leftTerm.set(lastInput.value);
				}
				break;
			case ActionType::Or:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{
				
					m_leftExpression.or(lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{
			
					m_leftTerm.set(lastInput.value);
				}
				break;
			case ActionType::Xor:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{

					m_leftExpression.xor(lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{

					m_leftTerm.set(lastInput.value);
				}
				break;
			case ActionType::Not:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{

					m_leftExpression.not();
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{

					m_leftTerm.set(lastInput.value);
				}
				break;
			}
			m_actions.push_back(input);
			return true;
		}
	}
	return false;
}