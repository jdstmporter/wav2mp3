#!/usr/bin/python3
'''
Created on 1 Dec 2017

@author: julianporter
'''
from setuptools import setup, Extension
from setuptools.config import read_configuration
import utils
from sys import exit

checker=utils.CheckLibrary("mp3lame")
checker.test()
if not checker['mp3lame']:
    print("Cannot build pcm2mp3 unless libmp3lame is installed and on the compiler path")
    exit(1)

configuration=read_configuration('setup.cfg')
metadata=configuration['metadata']

package=metadata['name']

libsrc=['MP3Encoder.cpp','PCMFile.cpp', 'WAVFile.cpp','AIFFFile.cpp', 'AIFFData.cpp',
        'base.cpp', 'Conversions.cpp', 'Iterator32.cpp','transcoder.cpp']
wsrc=['lib/'+s for s in libsrc]
wsrc.append('Lame.cpp')
qsrc=['Member.cpp','Quality.cpp']
rsrc=['Member.cpp','Rates.cpp']
version=metadata['version']

def makeExtension(module,src):
    majorV,minorV = version.split('.')
    return Extension(package+'.'+module,
                    define_macros = [('MAJOR_VERSION', majorV),
                                     ('MINOR_VERSION', minorV)],
                    sources = ['cpp/'+s for s in src],
                    language = 'c++',
                    include_dirs=['/usr/include'],
                    libraries = ['mp3lame'],
                    library_dirs = ['/usr/lib/x86_64-linux-gnu'])

coder = makeExtension('_pcm2mp3',wsrc)
rates = makeExtension('rates',rsrc)
quality = makeExtension('quality',qsrc)

setup (
    entry_points = {
        'distutils.commands' : [
           'cleaner = utils:Cleaner' 
           ]
        },
    ext_modules = [coder,rates,quality],
    
    )
