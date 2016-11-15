# -*- coding: utf-8 -*-
"""
Created on Tue Oct 13 15:09:53 2015

@author: TinoValentin
"""

import matplotlib.animation as animation
from numpy import *
from matplotlib.pylab import*
from pylab import *


def ani_error(Array,path,fps):
    plt.rcParams['animation.ffmpeg_path']='C:/ffmpeg/bin/ffmpeg.exe'
    writer=animation.FFMpegWriter(bitrate=300, fps = fps)
    
    length = len(Array)
    x = range(length)
    y = Array
    
    fig, ax = plt.subplots()
    line, = ax.plot(x, y, color='k')
    gca().get_yaxis().get_major_formatter().set_powerlimits((0, 0))
    line.axes.axis([0, length, min(y), max(y)])
    
    def update(num, x, y, line):
        line.set_data(x[:num], y[:num])
        return line,
    
    ani = animation.FuncAnimation(fig, update, len(x), fargs=[x, y, line],
                                  interval=50, blit=True)
    dpi = 300
#    writer = animation.writers['ffmpeg'](fps=fps, bitrate=500)
    ani.save(path,writer=writer,dpi=dpi)
    print("done with movie")
    plt.close()

def ani_frame(Array, path, title,fps):
    plt.rcParams['animation.ffmpeg_path']='C:/ffmpeg/bin/ffmpeg.exe'
    writer=animation.FFMpegWriter(bitrate=500, fps = fps)
    
    fig = plt.figure()
    fig.suptitle(title)
    ax = fig.add_subplot(111)
    ax.set_aspect('equal')
    length = shape(Array)[2]
    im = ax.imshow(Array[:,:,0], animated = True, cmap = "terrain_r")
    fig.colorbar(im)
    dpi = 150
    
    tight_layout()



    def update_img(n):
        tmp = Array[:,:,n]
        im.set_data(tmp)
        return im

    ani = animation.FuncAnimation(fig,update_img,length,interval=7)
    plt.show()
#    writer = animation.writers['ffmpeg'](fps=fps)

    ani.save(path,writer=writer,dpi=dpi)
    print("done with movie")
    plt.close()
    
def repulsion_frame(Array, rep, path, title):
    
    plt.rcParams['animation.ffmpeg_path']='C:/ffmpeg/bin/ffmpeg.exe'
    writer=animation.FFMpegWriter(bitrate=500, fps = fps)
    
    fig = plt.figure()
    fig.suptitle(title)
    ax = fig.add_subplot(112)
    ax.set_aspect('equal')
    length = shape(Array)[2]
    im = ax.imshow(Array[:,:,0], animated = True, cmap = "terrain_r")
    fig.colorbar(im)
    
    ax2 = fig.add_subplot(212)
    im2 = ax2.imshow(rep[:,:,0], animated = True, cmap ="terrain_r")
    dpi = 130
    
    tight_layout()


    def update_img(n):
        tmp = Array[:,:,n]
        tm2 = rep[:,:,n]
        im.set_data(tmp)
        im2.set_data(tm2)

    ani = animation.FuncAnimation(fig,update_img,length,interval=4)
    plt.show()
#    writer = animation.writers['ffmpeg'](fps=4)

    ani.save(path,writer=writer,dpi=dpi)
    print("done with movie")
    plt.close()


def sig_print(Arrays, path):
    fig_s = plt.figure()
    ax_s = fig_s.add_subplot(111)
    ax_s.semilogy(Arrays[:])
#    fig_s.suptitle("sigma" + "-Decay", fontsize=20)
#    plt.xlabel("#-sigma", fontsize=18)
#    plt.ylabel("sigma", fontsize=16)
    savefig(path, transparent=True, dpi=150)
    plt.close()
    
def print_frame(Array, path):
    fig, ax = plt.subplots()
    im = plt.imshow(Array, cmap="terrain_r")
    fig.colorbar(im, ax=ax)
    plt.savefig(path)
    plt.close()
    