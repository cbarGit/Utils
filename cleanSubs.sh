!#/bin/bash
#
#Script for changing every occurance of accented characters
#with one with no accent. For problems with some video player
#that don't accept unicode characters.
#
#USAGE:
#
#command [directory path]
#
#

inputdir=$1

echo "Correcting files.."

for file in $(find $inputdir -iname "*.srt") ; do
        echo Correct file $file
        sed -i "s/È/E'/g" $file
        sed -i "s/À/A'/g" $file
        sed -i "s/Ì/I'/g" $file
        sed -i "s/Ò/O'/g" $file
        sed -i "s/Ù/U'/g" $file
        sed -i "s/à/a'/g" $file
        sed -i "s/ò/o'/g" $file
        sed -i "s/ù/u'/g" $file
        sed -i "s/ì/i'/g" $file
        sed -i "s/é/e'/g" $file
        sed -i "s/è/e'/g" $file
done
