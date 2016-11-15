from tkinter import*
import numpy as np
import matplotlib.pylab as plt
from movie import*
#import aggdraw

def hexcoord(startx, starty, height, width):
    coordinates = [None]*12
    coordinates[0] = startx
    coordinates[1] = starty
    coordinates[2] = startx + width/2
    coordinates[3] = starty 
    coordinates[4] = startx + 3/4*width
    coordinates[5] = starty + height/2
    coordinates[6] = coordinates[2]
    coordinates[7] = coordinates[3] + height
    coordinates[8] = coordinates[0]
    coordinates[9] = coordinates[1] + height
    coordinates[10]= startx - width/4
    coordinates[11]= starty + height/2
    return coordinates
    
    
def pheromovie(length):
    plt.rcParams['animation.ffmpeg_path']='C:/ffmpeg/bin/ffmpeg.exe'
    writer=animation.FFMpegWriter(bitrate=500, fps = 5)
    
    fig = plt.figure()
    fig.suptitle(title)
    ax = fig.add_subplot(111)
    ax.set_aspect('equal')
    firstim = np.loadtxt("0Field.txt")
    firstim[50,50] = 0
    im = ax.imshow(firstim, animated = True, cmap = "terrain_r")
    fig.colorbar(im)
    dpi = 150
    
    tight_layout()



    def update_img(n):
        path = str(n) + "Field.txt"
        tmp = np.loadtxt(path)
#        tmp[250,250] = 0
        im.set_data(tmp)
        return im

    ani = animation.FuncAnimation(fig,update_img,length,interval=7)
    plt.show()
#    writer = animation.writers['ffmpeg'](fps=fps)

    ani.save("pheromovie.mp4",writer=writer,dpi=dpi)
    print("done with movie")
    plt.close()
    
def posmovie(length):
    plt.rcParams['animation.ffmpeg_path']='C:/ffmpeg/bin/ffmpeg.exe'
    writer=animation.FFMpegWriter(bitrate=200, fps = 10)
    
    fig = plt.figure()
    fig.suptitle(title)
    ax = fig.add_subplot(111)
    ax.set_aspect('equal')
    pos = np.loadtxt("animation.txt")
    
    for i in range(0,50,2):
        im = ax.scatter(pos[0,i],pos[0,i+1])
    im = ax.scatter(0,0)
    im = ax.scatter(200,0)
    im = ax.scatter(0,200)
    im = ax.scatter(200,200)
    dpi = 150
    
    tight_layout()



    def update_img(n):
        ax.clear()
        for i in range(0,50,2):
            im = ax.scatter(pos[n,i],pos[n,i+1])
#            im.set_data(tmp)
        im = ax.scatter(0,0)
        im = ax.scatter(200,0)
        im = ax.scatter(0,200)
        im = ax.scatter(200,200)
        return im

    ani = animation.FuncAnimation(fig,update_img,length,interval=7)
    plt.show()
#    writer = animation.writers['ffmpeg'](fps=fps)

    ani.save("psomovie.mp4",writer=writer,dpi=dpi)
    print("done with movie")
    plt.close()
    

if __name__ == "__main__":
    index = 0
    
    field = np.loadtxt("4Field.txt")
#    
#    sizex = np.shape(field)[1]
#    sizey = np.shape(field)[1]
#    sizewindow = 1500
##    
##    
#    sizex = sizey = 10
#    width  = 0.95*sizewindow/sizex
#    height = np.sqrt(3)/2*width
#    startx = 100
#    starty = 100
##    
##    
#    field[250,250] = 0
#    posmovie(3000)
    pheromovie(50)
#    master = Tk()
#    w = Canvas(master, width=sizewindow, height=sizewindow)
#    w.config(bg='white')
#    a = hexcoord(startx,starty,height,width)
##    w.create_polygon(a,     outline='black', 
##                     fill='gray', width=2)
#                     
#    for j in range(sizex):
#        for i in range(sizey):
#            a = hexcoord(a[0],a[1]+height,height,width)
##            if field[i,j]:
##                print(i,j)
##                w.create_polygon(a,     outline='black', 
##                        fill='blue', width=1)
##            else:
#            w.create_polygon(a,     outline='black', 
#                        fill='grey', width=1) 
#                        
#        a[0] += 3/4*width
#        if j%2:
#            a[1] -= (sizey-0.5)*height
#        else:
#            a[1] -= (sizey+0.5)*height
            
    
#    for i in range(2):
#        w.create_polygon(a,     outline='black', 
#                fill='gray', width=2)
#        w.pack()
#        if i%2==0:
#            a = hexcoord(a[2],a[3],height,width)
#        else:
#            a = hexcoord(a[7],a[8], height,width)
    plt.imshow(field, interpolation ="None")
    plt.colorbar()
#    w.pack()
#    mainloop()