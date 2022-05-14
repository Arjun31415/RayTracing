let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
let Lf_PopupWidth =  74 
let UltiSnipsExpandTrigger = "<tab>"
let WebDevIconsNerdTreeGitPluginForceVAlign =  1 
let Lf_PopupColorscheme = "gruvbox_material"
let UltiSnipsJumpForwardTrigger = "<tab>"
let DevIconsEnableFoldersOpenClose =  0 
let TrailingWhitespace_ns =  24 
let UltiSnipsRemoveSelectModeMappings =  0 
let WebDevIconsNerdTreeAfterGlyphPadding = " "
let WebDevIconsUnicodeByteOrderMarkerDefaultSymbol = ""
let DevIconsEnableFolderExtensionPatternMatching =  0 
let DevIconsEnableDistro =  1 
let WebDevIconsUnicodeDecorateFileNodes =  1 
let DevIconsEnableFolderPatternMatching =  1 
let WebDevIconsUnicodeDecorateFolderNodesDefaultSymbol = ""
let WebDevIconsTabAirLineAfterGlyphPadding = ""
let DevIconsArtifactFixChar = " "
let Lf_ShortcutB = ""
let Lf_WorkingDirectoryMode = "a"
let WebDevIconsUnicodeDecorateFileNodesDefaultSymbol = ""
let NERDTreeGitStatusUpdateOnCursorHold =  1 
let WebDevIconsUnicodeDecorateFolderNodesExactMatches =  1 
let UltiSnipsEnableSnipMate =  0 
let DevIconsAppendArtifactFix =  0 
let Lf_UseVersionControlTool =  0 
let WebDevIconsUnicodeDecorateFolderNodes =  1 
let WebDevIconsNerdTreeBeforeGlyphPadding = " "
let WebDevIconsUnicodeDecorateFolderNodesSymlinkSymbol = ""
let UltiSnipsJumpBackwardTrigger = "<S-Tab>"
let Lf_DefaultMode = "NameOnly"
let WebDevIconsUnicodeGlyphDoubleWidth =  1 
let Lf_ShowHidden =  1 
let XkbSwitchEnabled =  1 
let NERDTreeUpdateOnCursorHold =  1 
let Lf_ShortcutF = ""
let DevIconsDefaultFolderOpenSymbol = ""
let Lf_DefaultExternalTool = "rg"
let Lf_UseMemoryCache =  0 
let Lf_UseCache =  0 
let WebDevIconsTabAirLineBeforeGlyphPadding = " "
silent only
silent tabonly
cd /mnt/shared/CODING/cpp-graphics/src
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
set shortmess=aoO
badd +34 /mnt/shared/CODING/cpp-graphics/src/include/Player.cpp
argglobal
%argdel
$argadd .
edit /mnt/shared/CODING/cpp-graphics/src/include/Player.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
balt /mnt/shared/CODING/cpp-graphics/src/include/Player.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 34 - ((3 * winheight(0) + 23) / 47)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 34
normal! 013|
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
