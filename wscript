#!/usr/bin/env python
# encoding: utf-8

APPLICATION_NAME='audio_trigger'

VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_REVISION = 1

VERSION=str(VERSION_MAJOR)+'.'+str(VERSION_MINOR)+'.'+str(VERSION_REVISION)

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx')

    conf.define('VERSION', VERSION)
    conf.define('APPLICATION_NAME', APPLICATION_NAME)

    #conf.env.CXXFLAGS = ['-Wall', '-g']

    conf.check_cfg(package='gtkmm-3.0', at_least_version='3.0.0', args='--cflags --libs', uselib_store='GTKMM3')

    conf.write_config_header('config.h')


def build(bld):
    
    SOURCES_PATTERN = ['src/**.cc', 'src/ui/**.cc']
    TESTS_PATTERN   = 'src/**/tests/**.cc'
    MAINS_PATTERN   = 'src/main.cc'

    # Compile program
    bld.program(
        source   = bld.path.ant_glob(SOURCES_PATTERN, excl=[TESTS_PATTERN]),
        includes = '.',
        target   = APPLICATION_NAME,
        use      = 'GTKMM3'
    )
