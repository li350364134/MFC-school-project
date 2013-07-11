// asd.cpp : implementation file
//

#include "stdafx.h"
#include "library.h"
#include "asd.h"
#include "Public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Casd dialog


Casd::Casd(CWnd* pParent /*=NULL*/)
	: CDialog(Casd::IDD, pParent)
{
	//{{AFX_DATA_INIT(Casd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Casd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Casd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Casd, CDialog)
	//{{AFX_MSG_MAP(Casd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Casd message handlers

void Casd::OnOK() 
{
	int i = 0,j,chartint;
	bool flag = false;
	CString chart, after, bookname;
	CStringArray newnum, newusernum;
	GetDlgItemText(IDC_EDIT1,bookname);
	CStdioFile file("filename.dat",CFile::modeRead|CFile::typeBinary);	
	while(file.ReadString(chart)) {
		i++;
		if (chart == bookname) {
			j = i;
			break;
		}	
	}
	file.SeekToBegin();
	file.Close();

	file.Open("usernum.txt",CFile::modeRead|CFile::typeBinary);	
	i = 0;
		while(file.ReadString(chart)) {
		i++;
		if (i == CPublic::usmark) {
			chartint = atoi(chart);
			if(chartint > 0) {
				chartint--;
				flag = true;
			}
			after.Format(_T("%d"), chartint);
			newusernum.Add(after);
		} else {
			newusernum.Add(chart);
		}
		
	}
	file.SeekToBegin();
	file.Close();

	file.Open("usernum.txt",CFile::modeWrite|CFile::modeCreate);
	file.Close();

	file.Open("usernum.txt",CFile::modeWrite|CFile::typeBinary);	
	i = 0;
	while(i < newusernum.GetSize()) {
		file.WriteString(newusernum.GetAt(i) + '\n');
		i++;
	}
	file.SeekToBegin();
	file.Close();

	file.Open("filenum.dat",CFile::modeRead|CFile::typeBinary);	
	i=0;
	while(file.ReadString(chart)) {
		i++;
		if (i == j) {
			chartint = atoi(chart);
			if (flag) {
				chartint++;
			}
			after.Format(_T("%d"), chartint);
			newnum.Add(after);
		} else {
			newnum.Add(chart);
		}
		
	}
	file.SeekToBegin();
	file.Close();

	file.Open("filenum.dat",CFile::modeWrite|CFile::modeCreate);
	file.Close();

	file.Open("filenum.dat",CFile::modeWrite|CFile::typeBinary);	
	i = 0;
	while (i < newnum.GetSize()) {
		file.WriteString(newnum.GetAt(i) + '\n');
		i++;
	}
	file.SeekToBegin();
	file.Close();
	
	CDialog::OnOK();
}
