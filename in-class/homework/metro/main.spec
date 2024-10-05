# -*- mode: python -*-

import os
from PyInstaller.utils.hooks import collect_data_files

# 获取 conda 环境路径
env_path = os.environ['CONDA_PREFIX']
dlls = os.path.join(env_path, 'DLLs')
bins = os.path.join(env_path, 'Library', 'bin')

# 设置路径
paths = [
    os.getcwd(),
    env_path,
    dlls,
    bins,
]

# 指定二进制文件
binaries = [
    (os.path.join(bins, 'geos.dll'), '.'),
    (os.path.join(bins, 'geos_c.dll'), '.'),
    (os.path.join(bins, 'spatialindex_c-64.dll'), '.'),
    (os.path.join(bins, 'spatialindex-64.dll'), '.'),
]

# 指定隐藏导入
hidden_imports = [
    'ctypes',
    'ctypes.util',
    'fiona',
    'fiona._shim',
    'gdal',
    'geos',
    'shapely',
    'shapely.geometry',
    'pyproj',
    'rtree',
    'pytest',
    'pandas._libs.tslibs.timedeltas',
]

# 收集 osgeo 的 .pyd 文件
_osgeo_pyds = collect_data_files('osgeo', include_py_files=True)
osgeo_pyds = [(p, '.') for p, lib in _osgeo_pyds if '.pyd' in p]

# 合并二进制文件
binaries += osgeo_pyds

# 收集 geopandas 数据文件
geopandas_datas = collect_data_files('geopandas', subdir='datasets')

# 添加其他数据文件
additional_datas = [
    ('beijing.json', '.'),
    ('metro.json', '.'),
    ('data.json', '.'),
    ('coordinate.csv', '.')
]

# 合并所有数据文件
datas = geopandas_datas + additional_datas

# 创建 Analysis 对象
a = Analysis(
    ['main.py'],
    pathex=paths,
    binaries=binaries,
    datas=datas,
    hiddenimports=hidden_imports,
    hookspath=[],
    runtime_hooks=[],
    excludes=[],
    win_no_prefer_redirects=False,
    win_private_assemblies=False,
    cipher=None
)

pyz = PYZ(a.pure)
exe = EXE(
    pyz,
    a.scripts,
    [],
    exclude_binaries=True,
    name='main',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    console=False,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
)
coll = COLLECT(
    exe,
    a.binaries,
    a.datas,
    strip=False,
    upx=True,
    upx_exclude=[],
    name='main',
)