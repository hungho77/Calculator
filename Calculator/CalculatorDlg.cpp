
// CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include <string>
#include <sstream>
#include "CalculatorApp.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_output);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
	DDX_Control(pDX, IDC_BUTTON0, m_button0);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_BUTTON3, m_button3);
	DDX_Control(pDX, IDC_BUTTON4, m_button4);
	DDX_Control(pDX, IDC_BUTTON5, m_button5);
	DDX_Control(pDX, IDC_BUTTON6, m_button6);
	DDX_Control(pDX, IDC_BUTTON7, m_button7);
	DDX_Control(pDX, IDC_BUTTON8, m_button8);
	DDX_Control(pDX, IDC_BUTTON9, m_button9);
	DDX_Control(pDX, IDC_BUTTON_EQUAL, m_buttonEQUAL);
	DDX_Control(pDX, IDC_BUTTON_PLUS, m_buttonPLUS);
	DDX_Control(pDX, IDC_BUTTON_MINUS, m_buttonMINUS);
	DDX_Control(pDX, IDC_BUTTON_MULTI, m_buttonMULTI);
	DDX_Control(pDX, IDC_BUTTON_DIV, m_buttonDIV);
	DDX_Control(pDX, IDC_BUTTON_CE, m_buttonCE);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_buttonDEL);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit1);
	DDX_Control(pDX, IDC_BUTTON_AND, m_buttonAnd);
	DDX_Control(pDX, IDC_BUTTON_OR, m_buttonOr);
	DDX_Control(pDX, IDC_BUTTON_XOR, m_buttonXor);
	DDX_Control(pDX, IDC_BUTTON_NOT, m_buttonNot);
	DDX_Control(pDX, IDC_BUTTON_DEC, m_buttonDec);
	DDX_Control(pDX, IDC_BUTTON_BIN, m_buttonBin);
	DDX_Control(pDX, IDC_BUTTON_HEX, m_buttonHex);
	DDX_Control(pDX, IDC_BUTTON_A, m_button10);
	DDX_Control(pDX, IDC_BUTTON_B, m_button11);
	DDX_Control(pDX, IDC_BUTTON_C, m_button12);
	DDX_Control(pDX, IDC_BUTTON_D, m_button13);
	DDX_Control(pDX, IDC_BUTTON_E, m_button14);
	DDX_Control(pDX, IDC_BUTTON_F, m_button15);
	DDX_Control(pDX, IDC_BUTTON_LSH, m_buttonLsh);
	DDX_Control(pDX, IDC_BUTTON_RSH, m_buttonRsh);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DEC, &CCalculatorDlg::OnBnClickedButtonDec)
	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT_RESULT, &CCalculatorDlg::OnEnChangeEditResult)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCalculatorDlg::OnBnClickedButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCalculatorDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MULTI, &CCalculatorDlg::OnBnClickedButtonMulti)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_CE, &CCalculatorDlg::OnBnClickedButtonCe)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CCalculatorDlg::OnBnClickedButtonDel)
	ON_EN_CHANGE(IDC_EDIT1, &CCalculatorDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON_AND, &CCalculatorDlg::OnBnClickedButtonAnd)
	ON_BN_CLICKED(IDC_BUTTON_OR, &CCalculatorDlg::OnBnClickedButtonOr)
	ON_BN_CLICKED(IDC_BUTTON_XOR, &CCalculatorDlg::OnBnClickedButtonXor)
	ON_BN_CLICKED(IDC_BUTTON_NOT, &CCalculatorDlg::OnBnClickedButtonNot)
	ON_BN_CLICKED(IDC_BUTTON_BIN, &CCalculatorDlg::OnBnClickedButtonBin)
	ON_BN_CLICKED(IDC_BUTTON_HEX, &CCalculatorDlg::OnBnClickedButtonHex)
	ON_BN_CLICKED(IDC_BUTTON_A, &CCalculatorDlg::OnBnClickedButtonA)
	ON_BN_CLICKED(IDC_BUTTON_B, &CCalculatorDlg::OnBnClickedButtonB)
	ON_BN_CLICKED(IDC_BUTTON_C, &CCalculatorDlg::OnBnClickedButtonC)
	ON_BN_CLICKED(IDC_BUTTON_D, &CCalculatorDlg::OnBnClickedButtonD)
	ON_BN_CLICKED(IDC_BUTTON_E, &CCalculatorDlg::OnBnClickedButtonE)
	ON_BN_CLICKED(IDC_BUTTON_F, &CCalculatorDlg::OnBnClickedButtonF)
	ON_BN_CLICKED(IDC_BUTTON_LSH, &CCalculatorDlg::OnBnClickedButtonLsh)
	ON_BN_CLICKED(IDC_BUTTON_RSH, &CCalculatorDlg::OnBnClickedButtonRsh)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_font.CreateFont(32, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Microsoft Sans Serif"));
	m_editResult.SetFont(&m_font);
	m_fontN.CreateFont(24, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Microsoft Sans Serif"));
	m_fontM.CreateFont(16, 0, 0, 0,FW_NORMAL , 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Microsoft Sans Serif"));
	m_button0.SetFont(&m_fontN);
	m_button1.SetFont(&m_fontN);
	m_button2.SetFont(&m_fontN);
	m_button3.SetFont(&m_fontN);
	m_button4.SetFont(&m_fontN);
	m_button5.SetFont(&m_fontN);
	m_button6.SetFont(&m_fontN);
	m_button7.SetFont(&m_fontN);
	m_button8.SetFont(&m_fontN);
	m_button9.SetFont(&m_fontN);
	m_button10.SetFont(&m_fontM);
	m_button11.SetFont(&m_fontM);
	m_button12.SetFont(&m_fontM);
	m_button13.SetFont(&m_fontM);
	m_button14.SetFont(&m_fontM);
	m_button15.SetFont(&m_fontM);
	m_calculator.mode = Calculator::Dec;
	m_strEdit1 = "Dec";
	reset();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::resetOutput()
{
	m_output = m_outputResetString;
}

void CCalculatorDlg::reset()
{
	m_calculator.reset();
	m_errorInput = false;
	m_firstDigitEntered = FALSE;
	resetOutput();
	UpdateData(FALSE);
}

void CCalculatorDlg::addDigit(char digit)
{
	if (m_errorInput)
		return;

	UpdateData();
	if (m_calculator.isOperation(m_calculator.getLastInput().actionType) &&
		!m_firstDigitEntered)
	{
		m_output = digit;
	}
	else
	{
		if (m_output == m_outputResetString && digit == '0')
			return; 
		else if (m_output == m_outputResetString)
			m_output = digit; 
		else
			m_output += digit; 
	}
	m_firstDigitEntered = TRUE;
	UpdateData(FALSE);
}

void CCalculatorDlg::doOperation(Calculator::ActionType operation, bool handleNumber)
{
	if (m_errorInput)
		return;

	UpdateData();
	Calculator::Action input;
	if (handleNumber)
	{
		input.actionType = Calculator::ActionType::Number;
		string s2((CStringA)m_output);
		switch (m_calculator.mode)
		{
		case Calculator::Mode::Dec:
			break;
		case Calculator::Mode::Bin:
		{
			s2 = case_Bin_To_Dec(s2);
			m_output = s2.c_str();
			break;
		}
		case Calculator::Mode::Hex:
		{
			s2 = case_Hex_To_Dec(s2);
			m_output = s2.c_str();
			break;
		}
		}
		DecStrToQInt(s2, input.value);
		m_calculator.addInput(input);
	}
	input.actionType = operation;
	m_errorInput = false;
	try
	{
		if (m_calculator.addInput(input))
		{
			if (!m_calculator.hasLeftTermValue() || !m_calculator.hasLeftExpressionValue())
			{
				std::string curResult = PrintQInt(m_calculator.getCurrentResult());
				switch (m_calculator.mode)
				{
				case Calculator::Mode::Dec:
					break;
				case Calculator::Mode::Bin:
				{
					curResult = case_Dec_To_Bin(curResult);
					m_output = curResult.c_str();
					break;
				}
				case Calculator::Mode::Hex:
				{
					curResult = case_Dec_To_Hex(curResult);
					m_output = curResult.c_str();
					break;
				}
				}
				m_output = "";
				m_output += curResult.c_str();
				UpdateData(FALSE);
			}
		}
		else 
			AfxMessageBox(_T("Error: An unknown operation."));
	}
	catch (std::exception& e)
	{
		m_output = e.what();
		m_firstDigitEntered = FALSE;
		m_errorInput = true;
	}
	UpdateData(FALSE);
	m_firstDigitEntered = FALSE;
}


void CCalculatorDlg::OnEnChangeEditResult()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CCalculatorDlg::OnBnClickedButton0()
{
	addDigit('0');
}

void CCalculatorDlg::OnBnClickedButton1()
{
	addDigit('1');
}

void CCalculatorDlg::OnBnClickedButton2()
{
	if (m_calculator.mode != Calculator::Mode::Bin)
		addDigit('2');
}


void CCalculatorDlg::OnBnClickedButton3()
{
	if (m_calculator.mode != Calculator::Mode::Bin)
		addDigit('3');
}

void CCalculatorDlg::OnBnClickedButton4()
{
	if (m_calculator.mode != Calculator::Mode::Bin)
		addDigit('4');
}


void CCalculatorDlg::OnBnClickedButton5()
{
	if (m_calculator.mode != Calculator::Mode::Bin)
		addDigit('5');
}


void CCalculatorDlg::OnBnClickedButton6()
{
	if (m_calculator.mode != Calculator::Mode::Bin)
		addDigit('6');
}


void CCalculatorDlg::OnBnClickedButton7()
{
	if (m_calculator.mode != Calculator::Mode::Bin)
		addDigit('7');
}


void CCalculatorDlg::OnBnClickedButton8()
{
	if (m_calculator.mode != Calculator::Mode::Bin)
		addDigit('8');
}


void CCalculatorDlg::OnBnClickedButton9()
{
	if (m_calculator.mode != Calculator::Mode::Bin)
		addDigit('9');
}


void CCalculatorDlg::OnBnClickedButtonEqual()
{
	doOperation(Calculator::ActionType::Equal);
}



void CCalculatorDlg::OnBnClickedButtonPlus()
{
	doOperation(Calculator::ActionType::Plus);
}



void CCalculatorDlg::OnBnClickedButtonMinus()
{
	doOperation(Calculator::ActionType::Minus);
}


void CCalculatorDlg::OnBnClickedButtonMulti()
{
	doOperation(Calculator::ActionType::Multi);
}



void CCalculatorDlg::OnBnClickedButtonDiv()
{
	doOperation(Calculator::ActionType::Div);
}


void CCalculatorDlg::OnBnClickedButtonCe()
{
	reset();
}


void CCalculatorDlg::OnBnClickedButtonDel()
{
	if (m_errorInput)
		return;

	UpdateData();
	if (m_firstDigitEntered == TRUE)
	{
		if (m_output == m_outputResetString)
			return;
		else
		{
			if (m_output.GetLength() == 1)
				m_output = m_outputResetString;
			else
			{
				int n = m_output.GetLength();
				m_output.Delete(n - 1, 1);
			}
		}
		UpdateData(FALSE);
	}
	else
		return;
}


void CCalculatorDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedButtonAnd()
{
	doOperation(Calculator::ActionType::And);
}

void CCalculatorDlg::OnBnClickedButtonOr()
{
	doOperation(Calculator::ActionType::Or);
}



void CCalculatorDlg::OnBnClickedButtonXor()
{
	doOperation(Calculator::ActionType::Xor);
}


void CCalculatorDlg::OnBnClickedButtonNot()
{
	doOperation(Calculator::ActionType::Not);
}

void CCalculatorDlg::OnBnClickedButtonDec()
{
	m_calculator.mode = Calculator::Mode::Dec;
	m_strEdit1 = "Dec";
	std::string curResult = PrintQInt(m_calculator.getCurrentResult());
	switch (m_calculator.mode)
	{
	case Calculator::Mode::Dec:
		break;
	case Calculator::Mode::Bin:
	{
		curResult = case_Dec_To_Bin(curResult);
		m_output = curResult.c_str();
		break;
	}
	case Calculator::Mode::Hex:
	{
		curResult = case_Dec_To_Hex(curResult);
		m_output = curResult.c_str();
		break;
	}
	}
	m_output = "";
	m_output += curResult.c_str();

	//setfont
	m_button0.SetFont(&m_fontN);
	m_button1.SetFont(&m_fontN);
	m_button2.SetFont(&m_fontN);
	m_button3.SetFont(&m_fontN);
	m_button4.SetFont(&m_fontN);
	m_button5.SetFont(&m_fontN);
	m_button6.SetFont(&m_fontN);
	m_button7.SetFont(&m_fontN);
	m_button8.SetFont(&m_fontN);
	m_button9.SetFont(&m_fontN);
	m_button10.SetFont(&m_fontM);
	m_button11.SetFont(&m_fontM);
	m_button12.SetFont(&m_fontM);
	m_button13.SetFont(&m_fontM);
	m_button14.SetFont(&m_fontM);
	m_button15.SetFont(&m_fontM);
	//end setfont
	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButtonBin()
{
	m_calculator.mode = Calculator::Mode::Bin;
	m_strEdit1 = "Bin";
	std::string curResult = PrintQInt(m_calculator.getCurrentResult());
	switch (m_calculator.mode)
	{
	case Calculator::Mode::Dec:
		break;
	case Calculator::Mode::Bin:
	{
		curResult = case_Dec_To_Bin(curResult);
		m_output = curResult.c_str();
		break;
	}
	case Calculator::Mode::Hex:
	{
		curResult = case_Dec_To_Hex(curResult);
		m_output = curResult.c_str();
		break;
	}
	}
	m_output = "";
	m_output += curResult.c_str();
	//setfont
	m_button0.SetFont(&m_fontN);
	m_button1.SetFont(&m_fontN);
	m_button2.SetFont(&m_fontM);
	m_button3.SetFont(&m_fontM);
	m_button4.SetFont(&m_fontM);
	m_button5.SetFont(&m_fontM);
	m_button6.SetFont(&m_fontM);
	m_button7.SetFont(&m_fontM);
	m_button8.SetFont(&m_fontM);
	m_button9.SetFont(&m_fontM);
	m_button10.SetFont(&m_fontM);
	m_button11.SetFont(&m_fontM);
	m_button12.SetFont(&m_fontM);
	m_button13.SetFont(&m_fontM);
	m_button14.SetFont(&m_fontM);
	m_button15.SetFont(&m_fontM);
	//end setfont
	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonHex()
{
	m_calculator.mode = Calculator::Mode::Hex;
	m_strEdit1 = "Hex";
	std::string curResult = PrintQInt(m_calculator.getCurrentResult());
	switch (m_calculator.mode)
	{
	case Calculator::Mode::Dec:
		break;
	case Calculator::Mode::Bin:
	{
		curResult = case_Dec_To_Bin(curResult);
		m_output = curResult.c_str();
		break;
	}
	case Calculator::Mode::Hex:
	{
		curResult = case_Dec_To_Hex(curResult);
		m_output = curResult.c_str();
		break;
	}
	}
	m_output = "";
	m_output += curResult.c_str();
	//setfont
	m_button0.SetFont(&m_fontN);
	m_button1.SetFont(&m_fontN);
	m_button2.SetFont(&m_fontN);
	m_button3.SetFont(&m_fontN);
	m_button4.SetFont(&m_fontN);
	m_button5.SetFont(&m_fontN);
	m_button6.SetFont(&m_fontN);
	m_button7.SetFont(&m_fontN);
	m_button8.SetFont(&m_fontN);
	m_button9.SetFont(&m_fontN);
	m_button10.SetFont(&m_fontN);
	m_button11.SetFont(&m_fontN);
	m_button12.SetFont(&m_fontN);
	m_button13.SetFont(&m_fontN);
	m_button14.SetFont(&m_fontN);
	m_button15.SetFont(&m_fontN);
	//end setfont
	UpdateData(FALSE);
}



void CCalculatorDlg::OnBnClickedButtonA()
{
	if (m_calculator.mode == Calculator::Mode::Hex)
		addDigit('A');
}


void CCalculatorDlg::OnBnClickedButtonB()
{
	if (m_calculator.mode == Calculator::Mode::Hex)
		addDigit('B');
}


void CCalculatorDlg::OnBnClickedButtonC()
{
	if (m_calculator.mode == Calculator::Mode::Hex)
		addDigit('C');
}


void CCalculatorDlg::OnBnClickedButtonD()
{
	if (m_calculator.mode == Calculator::Mode::Hex)
		addDigit('D');
}


void CCalculatorDlg::OnBnClickedButtonE()
{
	if (m_calculator.mode == Calculator::Mode::Hex)
		addDigit('E');
}


void CCalculatorDlg::OnBnClickedButtonF()
{
	if (m_calculator.mode == Calculator::Mode::Hex)
		addDigit('F');
}


void CCalculatorDlg::OnBnClickedButtonLsh()
{
	doOperation(Calculator::ActionType::Lsh);
}


void CCalculatorDlg::OnBnClickedButtonRsh()
{
	doOperation(Calculator::ActionType::Rsh);
}
