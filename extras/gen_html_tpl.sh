#!/usr/bin/env bash

IFS=

OUT_DIR="../src/inc"
rm -rf ${OUT_DIR}
mkdir ${OUT_DIR}

CLOSURE_COMPILER_JAR="contrib/closure-compiler/closure-compiler-v20180101.jar"

#$1=html source file
#$2=begin_tag
#$3=end_tag
#$4=out file
get_strip_content() {
    local src=$(cat $1)
    if [[ $src =~ $2(.+)$3 ]]
    then
        delimiter="D${RANDOM}"
        out=`echo "${BASH_REMATCH[1]}" | uglifycss`
#        out=`echo "${BASH_REMATCH[1]}"`
        out="R\"$delimiter(${out})$delimiter\";";
        echo ">>> generate ${OUT_DIR}/$4"
        echo ${out} > "${OUT_DIR}/$4"
    fi
}

get_strip_content_js() {
    local src=$(cat $1)
    if [[ $src =~ $2(.+)$3 ]]
    then
        delimiter="D${RANDOM}"
        out=`echo "${BASH_REMATCH[1]}" | java -jar contrib/closure-compiler/closure-compiler-v20180101.jar`
#        out=`echo "${BASH_REMATCH[1]}"`
        out="R\"$delimiter(${out})$delimiter\";";
        echo ">>> generate ${OUT_DIR}/$4"
        echo ${out} > "${OUT_DIR}/$4"
    fi
}

begin_tag="/\\*CONTENT_BEGIN\\*/"
end_tag="/\\*CONTENT_END\\*/"
file="glmt.css"
get_strip_content glmt.css $begin_tag $end_tag $file

begin_tag="// CONTENT_BEGIN"
end_tag="// CONTENT_END"
file="glmt.js"
get_strip_content_js glmt.js $begin_tag $end_tag $file


layout_html="layout.html"

begin_tag="<!--ELEM_BEGIN HTML_HEADER-->"
end_tag="<!--ELEM_END HTML_HEADER-->"
file="html_header.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="<!--ELEM_BEGIN ROOT_PAGE_HEADER-->"
end_tag="<!--ELEM_END ROOT_PAGE_HEADER-->"
file="html_root_page_header.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="<!--ELEM_BEGIN MENU_BEGIN-->"
end_tag="<!--ELEM_END MENU_BEGIN-->"
file="html_menu_begin.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="<!--ELEM_BEGIN MENU_END-->"
end_tag="<!--ELEM_END MENU_END-->"
file="html_menu_end.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="<!--ELEM_BEGIN ROOT_MENU_ITEMS-->"
end_tag="<!--ELEM_END ROOT_MENU_ITEMS-->"
file="html_root_menu_items.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="<!--ELEM_BEGIN MENU_ITEM-->"
end_tag="<!--ELEM_END MENU_ITEM-->"
file="html_menu_item.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="<!--ELEM_BEGIN HTML_END-->"
end_tag="<!--ELEM_END HTML_END-->"
file="html_end.html"
get_strip_content $layout_html $begin_tag $end_tag $file



layout_html="layout_wifi.html"

begin_tag="<!--ELEM_BEGIN CHILD_PAGE_HEADER-->"
end_tag="<!--ELEM_END CHILD_PAGE_HEADER-->"
file="html_child_page_header.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="<!--ELEM_BEGIN WIFI_MENU_SCAN_ITEM-->"
end_tag="<!--ELEM_END WIFI_MENU_SCAN_ITEM-->"
file="html_wifi_menu_scan_item.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="<!--ELEM_BEGIN WIFI_FROM_START-->"
end_tag="<!--ELEM_END WIFI_FROM_START-->"
file="html_wifi_from_start.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="<!--ELEM_BEGIN WIFI_FROM_PARAM-->"
end_tag="<!--ELEM_END WIFI_FROM_PARAM-->"
file="html_wifi_from_param.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="<!--ELEM_BEGIN WIFI_FROM_END-->"
end_tag="<!--ELEM_END WIFI_FROM_END-->"
file="html_wifi_from_end.html"
get_strip_content $layout_html $begin_tag $end_tag $file


layout_html="layout_info.html"
begin_tag="<!--ELEM_BEGIN INFO-->"
end_tag="<!--ELEM_END INFO-->"
file="html_info.html"
get_strip_content $layout_html $begin_tag $end_tag $file


layout_html="layout_mon.html"
begin_tag="<!--ELEM_BEGIN SERIAL_MONITOR-->"
end_tag="<!--ELEM_END SERIAL_MONITOR-->"
file="html_serial_monitor.html"
get_strip_content $layout_html $begin_tag $end_tag $file

begin_tag="// CONTENT_BEGIN"
end_tag="// CONTENT_END"
file="glmt_mon.js"
get_strip_content_js glmt_mon.js $begin_tag $end_tag $file
