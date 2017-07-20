#pragma once
/*
 *      Copyright (C) 2015 Team KODI
 *      http:/kodi.tv
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <queue>

#include "include/cef_render_handler.h"
#include "WebBrowserClientBase.h"

class CWebBrowserClientOpenGL :
  public CWebBrowserClientBase
{
public:
  CWebBrowserClientOpenGL(int iUniqueClientId, const WEB_ADDON_GUI_PROPS *props);
  virtual ~CWebBrowserClientOpenGL();

  virtual bool Initialize();
  virtual bool OpenWebsite(const char* strURL, bool single, bool allowMenus);

  /*!
   * Kodi add-on render functions
   */
  virtual void Cleanup();
  virtual void Render();

  /*!
   * CEF class handler alignment
   */
  IMPLEMENT_REFCOUNTING(CWebBrowserClientOpenGL);
  virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE { return this; }

  /*!
   * CefLifeSpanHandler functions
   */
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

  /*!
   * CefRenderHandler functions
   */
  virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) OVERRIDE;
  virtual bool GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX, int viewY, int& screenX, int& screenY) OVERRIDE;
  virtual void OnPaint(CefRefPtr<CefBrowser> browser,
                       PaintElementType type,
                       const RectList& dirtyRects,
                       const void* buffer,
                       int width, int height) OVERRIDE;

private:
  bool            m_bInitialized;          /*!< Render initialization done flag, becomes called on first OnPaint call */
  unsigned int    m_iTextureId;
  int             m_iViewWidth;
  int             m_iViewHeight;
  float           m_fSpinX;
  float           m_fSpinY;
  CefRect         m_popupRect;
  CefRect         m_updateRect;
  OnPaintMessage  m_onPaintMessage;
  P8PLATFORM::CMutex m_Mutex;

  static void OnPaint(void *msg);
};
