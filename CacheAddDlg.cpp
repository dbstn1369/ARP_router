// CacheAddDlg.cpp : implementation file

// 헤더파일 참조
#include "stdafx.h"
#include "ARP.h"
#include "CacheAddDlg.h"

#ifdef _DEBUGs
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CCacheAddDlg::CCacheAddDlg(CWnd* pParent /*=NULL*/)
   : CDialog(CCacheAddDlg::IDD, pParent)
{
   m_etherAddr = _T("");
}

void CCacheAddDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_IPADDRESS_IP_ADDR, m_IPAddr);
   DDX_Text(pDX, IDC_EDIT_ETHER_ADDR, m_etherAddr);
}

BEGIN_MESSAGE_MAP(CCacheAddDlg, CDialog)
END_MESSAGE_MAP()

void CCacheAddDlg::OnOK() 
{   
   UpdateData(true);

   bool isRight = false;

   if(m_etherAddr.GetLength() == 17) 
   {
      int i = 0;

      for(i; i < 17; i++) 
      {
         char c = m_etherAddr.GetAt(i);
         if( (i + 1) % 3 == 0 )
         {
            if( c != '-' )
               break;
         }
         else if( !( ( c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9') ) )
            break;
      }
      if(i == 17)
         isRight = true;
   }
   if(m_etherAddr.IsEmpty() || m_IPAddr.IsBlank()) 
   {
      AfxMessageBox( "입력되지 않은 항목이 있습니다." );
      return;
   }
   else if( isRight == false ) 
   {
      AfxMessageBox( "주소형식이 올바르지 않습니다.( FORMAT : xx-xx-xx-xx-xx-xx )" );
      return;
   }
   
   m_IPAddr.GetAddress(m_buffer.buffer_IPAddr[0], m_buffer.buffer_IPAddr[1], m_buffer.buffer_IPAddr[2], m_buffer.buffer_IPAddr[3]);
   
   for(int i = 0; i < 10; i++)
   {
      CString temp;
      unsigned char char_temp[10];
      
      AfxExtractSubString(temp, m_etherAddr, i, '-');
      sscanf(temp,"%x", &char_temp[i]);
      m_buffer.buffer_EtherAddr[i] = char_temp[i];
   }
   
   CDialog::OnOK();
}

//getter
Cache_BufferAddr CCacheAddDlg::GetBufferAddr()
{
   return m_buffer;
}