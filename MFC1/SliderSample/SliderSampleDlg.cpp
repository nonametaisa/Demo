
// SliderSampleDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SliderSample.h"
#include "SliderSampleDlg.h"
#include "afxdialogex.h"
#include <chrono>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSliderSampleDlg ダイアログ



CSliderSampleDlg::CSliderSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SLIDERSAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	this->m_rainbow = new CBrush[this->m_rainbow_count];
	this->m_rainbow[0].CreateSolidBrush(RGB(254, 76, 66));
	this->m_rainbow[1].CreateSolidBrush(RGB(255, 161, 5));
	this->m_rainbow[2].CreateSolidBrush(RGB(255, 120, 4));
	this->m_rainbow[3].CreateSolidBrush(RGB(66, 192, 30));
	this->m_rainbow[4].CreateSolidBrush(RGB(17, 151, 245));
	this->m_rainbow[5].CreateSolidBrush(RGB(186, 93, 210));
}

void CSliderSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CHANGE, m_change_button);
	DDX_Control(pDX, IDC_BUTTON_REDRAW, m_redraw_button);
	DDX_Control(pDX, IDC_SLIDER, m_slider);
}

BEGIN_MESSAGE_MAP(CSliderSampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CSliderSampleDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_REDRAW, &CSliderSampleDlg::OnBnClickedButtonRedraw)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CSliderSampleDlg::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()


// CSliderSampleDlg メッセージ ハンドラー

BOOL CSliderSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CSliderSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CSliderSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSliderSampleDlg::OnBnClickedButtonChange()
{
	this->m_index = this->m_index++ % this->m_rainbow_count;
}

void CSliderSampleDlg::OnBnClickedButtonRedraw()
{
	const auto max = this->m_slider.GetRangeMax();
	const auto min = this->m_slider.GetRangeMin();

	// Set same value to redraw
	this->m_slider.SetRange(min, max, TRUE);
}

HBRUSH CSliderSampleDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	const HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_EDIT:
	case CTLCOLOR_STATIC:
		if (pWnd->m_hWnd == this->m_slider.m_hWnd)
		{
			pDC->SetBkMode(TRANSPARENT);
			return static_cast<HBRUSH>(this->m_rainbow[this->m_index]);
		}
	default:
		return hbr;
	}
}

void CSliderSampleDlg::OnBnClickedButtonUpdate()
{
	this->m_slider.UpdateWindow();
}
