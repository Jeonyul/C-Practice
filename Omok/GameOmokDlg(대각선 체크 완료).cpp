
// GameOmokDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "GameOmok.h"
#include "GameOmokDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGameOmokDlg 대화 상자



CGameOmokDlg::CGameOmokDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CGameOmokDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// My code
	mIndexOfRects = 0;
	memset(m_Data[0], 0, MAX_GRID_X * MAX_GRID_Y);
	m_CurrentStone = BLACK_STONE;

	for (int y = 0; y < MAX_GRID_Y; y++) {
		for (int x = 0; x < MAX_GRID_X; x++) {
			m_Rect[y][x].SetRect(START_POS_X + x*GRID_STEP_SIZE,
				START_POS_Y + y*GRID_STEP_SIZE,
				START_POS_X + (x + 1)*GRID_STEP_SIZE,
				START_POS_Y + (y + 1)*GRID_STEP_SIZE);
		}
	}
}
int CGameOmokDlg::ScanX(int type)
{
	int y, x;
	int equal_count = 0;

	for (y = 0; y < MAX_GRID_Y; y++)
	{
		equal_count = 0;
		for (x = 0; x < MAX_GRID_X; x++)
		{
			if (m_Data[y][x] && type == m_Data[y][x])
			{
				equal_count++;
				if (equal_count >= 5)
				{
					return TRUE;
				}
			}
			else
			{
				equal_count = 0;
			}
		}
	}
	return FALSE;
}
int CGameOmokDlg::ScanY(int type)
{
	int y, x;
	int equal_count = 0;

	for (x = 0; x < MAX_GRID_X; x++)
	{
		equal_count = 0;
		for (y = 0; y < MAX_GRID_Y; y++)
		{
			if (m_Data[y][x] && type == m_Data[y][x])
			{
				equal_count++;
				if (equal_count >= 5)
				{
					return TRUE;
				}
			}
			else
			{
				equal_count = 0;
			}
		}
	}
	return FALSE;
}
int CGameOmokDlg::ScanDiagonalBackslash(int type, int x, int y)
{
	int tempX = x;
	int tempY = y;
	int equalCount = 1;
	while (tempY - 1 >= 0 && tempX - 1 >= 0) // to top left
	{
		if (m_Data[tempY - 1][tempX - 1] && type == m_Data[tempY - 1][tempX - 1])
		{
			equalCount++;
			if (equalCount >= 5)
			{
				return TRUE;
			}
		}
		else
		{
			tempX = x;
			tempY = y;
			while (tempX + 1 < MAX_GRID_Y && tempY + 1 < MAX_GRID_Y) // to bottom right
			{
				if (m_Data[tempY + 1][tempX + 1] && type == m_Data[tempY + 1][tempX + 1])
				{
					equalCount++;
					if (equalCount >= 5)
					{
						return TRUE;
					}
				}
				else
				{
					equalCount = 0;
					return FALSE;
				}
				tempX++;
				tempY++;
			}
			return FALSE;
		}
		tempX--;
		tempY--;
	}
}
int CGameOmokDlg::ScanDiagonalSlash(int type, int x, int y)
{
	int tempX = x;
	int tempY = y;
	int equalCount = 1;
	while (tempY - 1 >= 0 && tempX + 1 < MAX_GRID_X) // to top right
	{
		if (m_Data[tempY - 1][tempX + 1] && type == m_Data[tempY - 1][tempX + 1])
		{
			equalCount++;
			if (equalCount >= 5)
			{
				return TRUE;
			}
		}
		else
		{
			tempX = x;
			tempY = y;
			while (tempX - 1 >= 0 && tempY + 1 < MAX_GRID_Y) // to bottom left
			{
				if (m_Data[tempY + 1][tempX - 1] && type == m_Data[tempY + 1][tempX - 1])
				{
					equalCount++;
					if (equalCount >= 5)
					{
						return TRUE;
					}
				}
				else
				{
					equalCount = 0;
					return FALSE;
				}
				tempX--;
				tempY++;
			}
			return FALSE;
		}
		tempX++;
		tempY--;
	}
}

void CGameOmokDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameOmokDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_NEW_BTN, &CGameOmokDlg::OnBnClickedNewBtn)
END_MESSAGE_MAP()


// CGameOmokDlg 메시지 처리기

BOOL CGameOmokDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_BkImage.LoadDibPath("resource/bk_image.bmp");
	m_BlackImage.LoadDibPath("resource/black.bmp");
	m_WhiteImage.LoadDibPath("resource/white.bmp");

	CClientDC dc(this);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGameOmokDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGameOmokDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		// Draw background Image
		m_BkImage.ShowDibImage(&dc, 0, 0);

		// Draw stones
		if (m_CurrentStone == BLACK_STONE)
		{
			m_BlackImage.ShowDibImage(&dc, 650, 100);
		}
		else
		{
			m_WhiteImage.ShowDibImage(&dc, 650, 100);
		}
		int colorSwitch = 1;
		for (int i = 0; i < mIndexOfRects; i++)
		{
			if (colorSwitch == 1)
			{
				m_BlackImage.DrawDIB(&dc, mRectsOfStonesOnBoard[i]);
				m_CurrentStone = WHITE_STONE;
				colorSwitch = 0;
			}
			else
			{
				m_WhiteImage.DrawDIB(&dc, mRectsOfStonesOnBoard[i]);
				m_CurrentStone = BLACK_STONE;
				colorSwitch = 1;
			}
		}


		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGameOmokDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGameOmokDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Draw a Stone
	CClientDC dc(this);
	for (int y = 0; y < MAX_GRID_Y; y++)
	{
		for (int x = 0; x < MAX_GRID_X; x++)
		{
			if (m_Rect[y][x].PtInRect(point))
			{

				/*CString str;
				str.Format("%d, %d", x, y);
				MessageBox(str);*/

				// Check there is a stone already
				bool isDuple = false;
				for (int i = 0; i < mIndexOfRects; i++)
				{
					if (mRectsOfStonesOnBoard[i] == m_Rect[y][x])
					{
						isDuple = true;
						break;
					}
				}

				if (isDuple)
				{
					MessageBox("이미 돌이 놓여있습니다");
					return;
				}
				else
				{
					mRectsOfStonesOnBoard[mIndexOfRects] = m_Rect[y][x];
					mIndexOfRects++;
					if (m_CurrentStone == BLACK_STONE)
					{
						m_BlackImage.DrawDIB(&dc, m_Rect[y][x]);
						m_Data[y][x] = BLACK_STONE;
						m_CurrentStone = WHITE_STONE;
						m_WhiteImage.ShowDibImage(&dc, 650, 100);
						if (ScanDiagonalBackslash(BLACK_STONE, x, y) == TRUE)
						{
							MessageBox("흑돌이 이겼습니다!!");
							return;
						}
						else if (ScanDiagonalSlash(BLACK_STONE, x, y) == TRUE)
						{
							MessageBox("흑돌이 이겼습니다!!");
							return;
						}
						else if (ScanX(BLACK_STONE) == TRUE)
						{
							MessageBox("흑돌이 이겼습니다!!");
							return;
						}
						else if (ScanY(BLACK_STONE) == TRUE)
						{
							MessageBox("흑돌이 이겼습니다!!");
							return;
						}
					}
					else
					{
						m_WhiteImage.DrawDIB(&dc, m_Rect[y][x]);
						m_Data[y][x] = WHITE_STONE;
						m_CurrentStone = BLACK_STONE;
						m_BlackImage.ShowDibImage(&dc, 650, 100);
						if (ScanDiagonalBackslash(WHITE_STONE, x, y) == TRUE)
						{
							MessageBox("백돌이 이겼습니다!!");
							return;
						}
						else if (ScanDiagonalSlash(WHITE_STONE, x, y) == TRUE)
						{
							MessageBox("백돌이 이겼습니다!!");
							return;
						}
						else if (ScanX(WHITE_STONE) == TRUE)
						{
							MessageBox("백돌이 이겼습니다!!");
							return;
						}
						else if (ScanY(WHITE_STONE) == TRUE)
						{
							MessageBox("백돌이 이겼습니다!!");
							return;
						}
					}
				}
			}
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
void CGameOmokDlg::OnBnClickedNewBtn()
{
	memset(m_Data, 0, MAX_GRID_Y * MAX_GRID_X);
	memset(mRectsOfStonesOnBoard, 0, mIndexOfRects);
	mIndexOfRects = 0;
	m_CurrentStone = BLACK_STONE;
	Invalidate();
}
