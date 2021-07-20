import win32api, win32con
import time
def click(x,y):
    win32api.SetCursorPos((x,y))
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,x,y,0,0)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,x,y,0,0)
    time.sleep(4)

def move(x,y):
    win32api.SetCursorPos((x,y))
    time.sleep(4)
    
while(1):
    click(200,80)
    move(500,500)
    click(300,80)
    move(800,800)
end
