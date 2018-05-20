
// GameOmokDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "GameOmok.h"
#include "GameOmokDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
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


// CGameOmokDlg ��ȭ ����



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


// CGameOmokDlg �޽��� ó����

BOOL CGameOmokDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_BkImage.LoadDibPath("resource/bk_image.bmp");
	m_BlackImage.LoadDibPath("resource/black.bmp");
	m_WhiteImage.LoadDibPath("resource/white.bmp");

	CClientDC dc(this);


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CGameOmokDlg::OnPaint()
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
					MessageBox("�̹� ���� �����ֽ��ϴ�");
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
							MessageBox("�浹�� �̰���ϴ�!!");
							return;
						}
						else if (ScanDiagonalSlash(BLACK_STONE, x, y) == TRUE)
						{
							MessageBox("�浹�� �̰���ϴ�!!");
							return;
						}
						else if (ScanX(BLACK_STONE) == TRUE)
						{
							MessageBox("�浹�� �̰���ϴ�!!");
							return;
						}
						else if (ScanY(BLACK_STONE) == TRUE)
						{
							MessageBox("�浹�� �̰���ϴ�!!");
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
							MessageBox("�鵹�� �̰���ϴ�!!");
							return;
						}
						else if (ScanDiagonalSlash(WHITE_STONE, x, y) == TRUE)
						{
							MessageBox("�鵹�� �̰���ϴ�!!");
							return;
						}
						else if (ScanX(WHITE_STONE) == TRUE)
						{
							MessageBox("�鵹�� �̰���ϴ�!!");
							return;
						}
						else if (ScanY(WHITE_STONE) == TRUE)
						{
							MessageBox("�鵹�� �̰���ϴ�!!");
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
