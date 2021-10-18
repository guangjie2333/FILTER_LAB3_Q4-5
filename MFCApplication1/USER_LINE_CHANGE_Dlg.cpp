// USER_LINE_CHANGE_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "USER_LINE_CHANGE_Dlg.h"
#include "afxdialogex.h"


// USER_LINE_CHANGE_Dlg 对话框

IMPLEMENT_DYNAMIC(USER_LINE_CHANGE_Dlg, CDialogEx)

USER_LINE_CHANGE_Dlg::USER_LINE_CHANGE_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LINER, pParent)
{

}

USER_LINE_CHANGE_Dlg::~USER_LINE_CHANGE_Dlg()
{
}

void USER_LINE_CHANGE_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(USER_LINE_CHANGE_Dlg, CDialogEx)
	ON_COMMAND(ID_32774, &USER_LINE_CHANGE_Dlg::Button_Up)
END_MESSAGE_MAP()


// USER_LINE_CHANGE_Dlg 消息处理程序


void USER_LINE_CHANGE_Dlg::Button_Up()
{
	// TODO: 在此添加命令处理程序代码
	
}
