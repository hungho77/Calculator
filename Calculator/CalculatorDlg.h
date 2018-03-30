
// CalculatorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include"Calculator.h"
#include<memory>

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	bool m_errorInput = false;
	const CString m_outputResetString{ "0" };
	void resetOutput();
	void reset();
	void addDigit(char digit);
	void doOperation(Calculator::ActionType operation, bool handleNumber = true);

	//
	CString m_strEdit1;
	CEdit m_edit1;
	//
	Calculator m_calculator;
	CString m_output;
	CFont m_font;
	CFont m_fontN;
	CFont m_fontM;
	BOOL m_firstDigitEntered = FALSE;
	CEdit m_editResult;
	CButton m_button0;
	CButton m_button1;
	CButton m_button2;
	CButton m_button3;
	CButton m_button4;
	CButton m_button5;
	CButton m_button6;
	CButton m_button7;
	CButton m_button8;
	CButton m_button9;
	CButton m_buttonA;
	CButton m_buttonB;
	CButton m_buttonC;
	CButton m_buttonD;
	CButton m_buttonE;
	CButton m_buttonF;
	CButton m_buttonDEC;
	CButton m_buttonHEX;
	CButton m_buttonBIN;
	CButton m_buttonAND;
	CButton m_buttonOR;
	CButton m_buttonXOR;
	CButton m_buttonNOT;
	CButton m_buttonEQUAL;
	CButton m_buttonMULTI;
	CButton m_buttonDIV;
	CButton m_buttonPLUS;
	CButton m_buttonMINUS;
	CButton m_buttonCE;
	CButton m_buttonDEL;
	CButton m_buttonAnd;
	CButton m_buttonOr;
	CButton m_buttonXor;
	CButton m_buttonNot;
	CButton m_buttonDec;
	CButton m_buttonBin;
	CButton m_buttonHex;


public:
	afx_msg void OnEnChangeEditResult();
	afx_msg void OnBnClickedButtonDec();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonEqual();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMulti();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonCe();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnEnChangeEdit1();

	afx_msg void OnBnClickedButtonAnd();
	afx_msg void OnBnClickedButtonOr();
	afx_msg void OnBnClickedButtonXor();
	afx_msg void OnBnClickedButtonNot();
	afx_msg void OnBnClickedButtonBin();
	afx_msg void OnBnClickedButtonHex();
	

	CButton m_button10;
	afx_msg void OnBnClickedButtonA();
	CButton m_button11;
	afx_msg void OnBnClickedButtonB();
	CButton m_button12;
	afx_msg void OnBnClickedButtonC();
	CButton m_button13;
	afx_msg void OnBnClickedButtonD();
	CButton m_button14;
	afx_msg void OnBnClickedButtonE();
	CButton m_button15;
	afx_msg void OnBnClickedButtonF();

	afx_msg void OnBnClickedButtonLsh();
	afx_msg void OnBnClickedButtonRsh();
	CButton m_buttonLsh;
	CButton m_buttonRsh;
};
