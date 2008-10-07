#!/bin/sh

rsync -e ssh --exclude=autom4te.cache --delete -av ~/development/spear/ \
	roasted:/usr/local/www/syzdek.net/htdocs/spear

