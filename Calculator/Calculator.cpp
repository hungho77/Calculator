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
		action == ActionType::Or || action == ActionType::Xor || action == ActionType::Not
		|| action == ActionType::Lsh || action == ActionType::Rsh);
}

bool Calculator::isTerm(ActionType action) const
{
	return (action == ActionType::Multi || action == ActionType::Div);
}

bool Calculator::isExpression(ActionType action) const
{
	return (action == ActionType::Plus || action == ActionType::Minus ||
		action == ActionType::And || action == ActionType::Or ||
		action == ActionType::Xor || action == ActionType::Not
		|| action == ActionType::Lsh || action == ActionType::Rsh);
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
	return m_leftExpression.hasValue() ? m_leftExpression.getValue() : m_leftTerm.getValue();
}

bool Calculator::addInput(const Action& input)
{
	const Calculator::Action lastInput = getLastInput();

	if (input.actionType == ActionType::Number)
	{
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
					m_leftExpression.add(lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{
					m_leftTerm.set(lastInput.value);
				}
				break;
			case ActionType::Minus:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{
					m_leftExpression.add(-lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{
					m_leftTerm.set(-lastInput.value);
				}
				break;
			case ActionType::Multi:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{
					m_leftExpression.add(m_leftTerm.getValue() * lastInput.value);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType)) 
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
						m_leftExpression.add(m_leftTerm.getValue() / lastInput.value);
						m_leftTerm.reset();
					}
				}
				else if (isTerm(input.actionType)) 
					m_leftTerm.multiBy(1 / lastInput.value);
				break;
			case ActionType::Equal: 
				if (isTerm(input.actionType))
				{
					m_leftExpression.reset();
					m_leftTerm.set(lastInput.value);
				}
				else if (isExpression(input.actionType))
				{
					m_leftExpression.set(lastInput.value);
					m_leftTerm.reset();
				}
			case ActionType::None:
				if (isTerm(input.actionType))
				{
					m_leftExpression.reset();
					m_leftTerm.set(lastInput.value);
				}
				else if (isExpression(input.actionType))
				{
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
			case ActionType::Lsh:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{
					int n = lastInput.value.data[3];
					m_leftExpression.lsh(n);
					m_leftTerm.reset();
				}
				else if (isTerm(input.actionType))
				{

					m_leftTerm.set(lastInput.value);
				}
				break;
			case ActionType::Rsh:
				if (isExpression(input.actionType) || input.actionType == ActionType::Equal)
				{
					int n = lastInput.value.data[3];
					m_leftExpression.rsh(n);
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