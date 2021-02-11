/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx	    = 7;
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = {"MesloLGS NF","Hack:size=10"};

static const char dmenufont[]       = "Hack:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red[] 	    = "#ff0000";
static const char col_purple[]      = "#9400D3";
static const char col_black[] 	    = "#000000";
static const char col_gray[]	    = "#545454";
static const char col_brightpurple[] = "#7F00FF";
static const char col_clear[] 	    = "#a9a9a9";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_gray },
	[SchemeSel]  = { col_brightpurple, col_black,  col_gray },
};

/* tagging */
static const char *tags[] = { "main", "2", "3", "4", "5", "6", "7", "8", "music" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       0,       0,           -1 },
	{ NULL, NULL, "Picture-in-Picture", 0, 1, -1 },
};

#include "horizgrid.c"
/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[][]",      tile },    /* first entry is default */
	{ "<>",      NULL },    /* no layout function means floating behavior */
	{ "[]",      monocle },
	{"###",	     horizgrid },
	{"HHH",	     grid },
	{NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINDOWS Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_gray3, "-sb", col_purple, "-sf", col_gray4, "-h", "30", NULL };
static const char *roficmd[] = {"rofi", "-show", NULL };

/*static const char *termcmd[]  = { "st", NULL };*/
static const char *termcmd[]  = { "alacritty", NULL };

/*command to lock lightdm and return to lightdm login screen */
static const char *lockcmd[] = { "dm-tool", "lock", NULL };
static const char *firefoxcmd[] = {"firefox", NULL };


/*brightness comamnds */
static const char *inc_brightness[] = {"xbacklight", "-inc", "5", NULL};
static const char *dec_brightness[] = {"xbacklight", "-dec", "5", NULL};

/*volume commands */
static const char *toggle_Mute[] = {"pactl", "set-sink-mute", "1", "toggle", NULL};
static const char *inc_volume[] = {"pactl", "set-sink-volume", "1", "+5%", NULL};
static const char *dec_volume[] = {"pactl", "set-sink-volume", "1", "-5%", NULL};

static const char *scrotcmd[] = {"sh", "$HOME/.scrot-select.sh", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = firefoxcmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = scrotcmd } },
	{ MODKEY,             		XK_F11,    spawn,          {.v = dec_brightness } },
	{ MODKEY,           		XK_F12,    spawn,          {.v = inc_brightness } },
	{ MODKEY,             		XK_F1,     spawn,          {.v = toggle_Mute } },
	{ MODKEY,             		XK_F2,     spawn,          {.v = dec_volume } },
	{ MODKEY,             		XK_F3,     spawn,          {.v = inc_volume } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_a,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_s,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,                       XK_comma,  cyclelayout,      {.i = -1 } },
	{ MODKEY|ShiftMask,                      XK_period,  cyclelayout,      {.i = +1 } },
	{ MODKEY,                       XK_space,  spawn,      	   {.v = roficmd} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_z,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_x,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_z,  	   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_x,	   tagmon,         {.i = +1 } },
	{ MODKEY,              			XK_w,      view_adjacent,  { .i = +1 } },
	{ MODKEY,             			XK_q,  	   view_adjacent,  { .i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_grave,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

