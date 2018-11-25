#!/bin/bash

function GetURL ()
{
   local URL=$1
   local DATE=$2
   local INDEX=$3
   
   echo "* Downloading entry: ${INDEX}"
   wget -q -O entries/${INDEX} "${URL}"
   
   echo "   Extracting contents."
   local storing_lines=0
   local first_line=1
   
   cat "entries/${INDEX}" | while read line
   do
      # I'm already looking for content lines?
      if [ "${storing_lines}" == "1" ]; then
         # Check if the line is an end for me.
         if [[ "${line}" == *posts-nav-link* ]]; then
            storing_lines=0
         # I'm storing lines. Check if the line is useful. For that, it should
         # be a paragraf.
         elif [ "${line:0:3}" == "<p>" ]; then
            # Is this the first line of the HTML?
            if [ "${first_line}" == "1" ]; then
               # It is a little bit longer. Make special process.
               local size=${#line}
               local length=$((size-4))
               local clean_line=dummy
               
               for i in {1..1000}
               do
                  if [ "${line:${i}:4}" == "</a>" ]; then
                     size=$((i+4))
                     clean_line=${line:${size}}
                  fi
               done
               
               for i in {1..1000}
               do
                  if [ "${clean_line:${i}:4}" == "</p>" ]; then
                     clean_line=${clean_line:0:${i}}
                  fi
               done
               
               echo "${clean_line}" >> contents/${INDEX}
               first_line=0
            else
               # It is an easy line. Remove the first 3 chars and last 4
               # It is something like "<p>LOL</p>"
               local size=${#line}
               local length=$((size-7))
               local clean_line=${line:3:${length}}
               echo "${clean_line}" >> contents/${INDEX}
            fi
         fi
      # No, check if the line contains the key I'm checking for
      elif [[ "${line}" == *articleBody* ]]; then
         # Enable flag
         storing_lines=1
      fi
   done
   
   echo "   Scanning contents."
   first_line=1
   local municipality=dummy
   local municipality_found=0
   local state=dummy
   local state_found=0   
   local keys_found=NONE
   local initial_size=0
   
   if [ -f "db.csv" ]; then
      initial_size=$(stat --printf="%s" db.csv)
   fi
   
   cat "contents/${INDEX}" | while read line
   do
      local remaining_line=dummy
      
      if [ "${first_line}" == "1" ]; then
         
         first_line=0
         
         for i in {1..50}
         do
            if [ "${municipality_found}" == "0" ]; then
               if [ "${line:${i}:1}" == "," ]; then
                  municipality=${line:0:${i}}
                  municipality_found=1
                  local index=$((i+2))
                  remaining_line=${line:${index}}
               fi
            fi
         done
         
         for i in {1..50}
         do
            if [ "${state_found}" == "0" ]; then
               if [ "${remaining_line:${i}:2}" == ".-" ]; then
                  state=${remaining_line:0:${i}}
                  state_found=1
                  local index=$((i+3))
                  remaining_line=${remaining_line:${index}}
               fi
            fi
         done
         
         if [ "${state_found}" == "1" ]; then
            # Add entry to the DB
            echo -n "${state},${municipality},${DATE},${INDEX}," >> db.csv
         fi
      else
         remaining_line=${line}
      fi
      
      # Don't scan if there isn't a state
      if [ "${state}" != "dummy" ]; then
         lowercase_string=${remaining_line,,}
         
         if [[ "${lowercase_string}" == *asesinada* ]]; then
            if [[ "${keys_found}" != *ASESINATO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASESINATO
                  echo -n "ASESINATO" >> db.csv
               else
                  keys_found="${keys_found}:ASESINATO"
                  echo -n ":ASESINATO" >> db.csv
               fi
            fi
         fi
                  
         if [[ "${lowercase_string}" == *asesinado* ]]; then
            if [[ "${keys_found}" != *ASESINATO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASESINATO
                  echo -n "ASESINATO" >> db.csv
               else
                  keys_found="${keys_found}:ASESINATO"
                  echo -n ":ASESINATO" >> db.csv
               fi
            fi
         fi
         
         if [[ "${lowercase_string}" == *dispararon* ]]; then
            if [[ "${keys_found}" != *DISPAROS* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=DISPAROS
                  echo -n "DISPAROS" >> db.csv
               else
                  keys_found="${keys_found}:DISPAROS"
                  echo -n ":DISPAROS" >> db.csv
               fi
            fi
         fi
         
         if [[ "${lowercase_string}" == *disparo* ]]; then
            if [[ "${keys_found}" != *DISPAROS* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=DISPAROS
                  echo -n "DISPAROS" >> db.csv
               else
                  keys_found="${keys_found}:DISPAROS"
                  echo -n ":DISPAROS" >> db.csv
               fi
            fi
         fi
         
         if [[ "${lowercase_string}" == *secuestrar* ]]; then
            if [[ "${keys_found}" != *SECUESTRO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=SECUESTRO
                  echo -n "SECUESTRO" >> db.csv
               else
                  keys_found="${keys_found}:SECUESTRO"
                  echo -n ":SECUESTRO" >> db.csv
               fi
            fi
         fi
         
         if [[ "${lowercase_string}" == *secuestro* ]]; then
            if [[ "${keys_found}" != *SECUESTRO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=SECUESTRO
                  echo -n "SECUESTRO" >> db.csv
               else
                  keys_found="${keys_found}:SECUESTRO"
                  echo -n ":SECUESTRO" >> db.csv
               fi
            fi
         fi
         
         if [[ "${lowercase_string}" == *secuestrad* ]]; then
            if [[ "${keys_found}" != *SECUESTRO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=SECUESTRO
                  echo -n "SECUESTRO" >> db.csv
               else
                  keys_found="${keys_found}:SECUESTRO"
                  echo -n ":SECUESTRO" >> db.csv
               fi
            fi
         fi
         
         if [[ "${lowercase_string}" == *robo* ]]; then
            if [[ "${keys_found}" != *ASALTO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASALTO
                  echo -n "ASALTO" >> db.csv
               else
                  keys_found="${keys_found}:ASALTO"
                  echo -n ":ASALTO" >> db.csv
               fi
            fi
         fi
         
         if [[ "${lowercase_string}" == *roba* ]]; then
            if [[ "${keys_found}" != *ASALTO* ]]; then
               if [ "${keys_found}" == "NONE" ]; then
                  keys_found=ASALTO
               else
                  keys_found="${keys_found}:ASALTO"
               fi
            fi
         fi
      fi
   done
   
   local final_size=0
   
   if [ -f "db.csv" ]; then
      final_size=$(stat --printf="%s" db.csv)
   fi
   
   if [ "${initial_size}" != "${final_size}" ]; then
      echo ",${URL}" >> db.csv
   fi
}

function CleanFolders ()
{
   echo "* Clear contents"
   echo "*"
   if [ -d "xmls/" ]; then
      rm -R xmls/
   fi
   mkdir xmls

   if [ -f "urls.txt" ]; then
      rm urls.txt
   fi
   
   if [ -f "db.csv" ]; then
      rm db.csv
   fi

   if [ -d "entries/" ]; then
      rm -R entries/
   fi
   mkdir entries

   if [ -d "contents/" ]; then
      rm -R contents/
   fi
   mkdir contents
}

# ********** #
# REAL START #
# ********** #

XML_URL=http://www.lapoliciaca.com/post_part
URL_KEY=loc
DATE_KEY=lastmod

CleanFolders

echo "* Downloading XML files."
# Download enough contents as to fill
for i in {1..2}
do
   output_file=""
   
   if [ ${i} -lt 10 ]; then
      output_file=xmls/p000${i}.xml
   elif [ ${i} -lt 100 ]; then
      output_file=xmls/p00${i}.xml
   elif [ ${i} -lt 1000 ]; then
      output_file=xmls/p0${i}.xml
   else
      output_file=xmls/p${i}.xml
   fi
   
   echo "* Downloading: ${output_file} <- ${XML_URL}${i}.xml"
   wget -q -O ${output_file} ${XML_URL}${i}.xml
done

echo "*"
echo "* Extracting files..."
for file in xmls/*
do
   echo "* Extracting file: ${file}"
   
   cat "${file}" | while read line
   do
      tmp=${line%<*}
      
      if [[ "${tmp}" == *${URL_KEY}* ]]; then
         echo "${tmp:5}" >> urls.txt
      elif [[ "${tmp}" == *${DATE_KEY}* ]]; then
         echo "${tmp:9}" >> urls.txt
      fi
   done
done

echo "*"
echo "* Getting pages contents..."
LINE_URL=dummy
LINE_DATE=dummy
BUFFERED=0
i=0
cat "urls.txt" | while read line
do
   if [ "${BUFFERED}" == "0" ]; then
      LINE_URL=${line}
      BUFFERED=1
   else
      LINE_DATE=${line}
      BUFFERED=0
      INDEX=dummy
      
      i=$((i+1))
      
      if [ $i -lt 10 ]; then
         INDEX=000${i}
      elif [ $i -lt 100 ]; then
         INDEX=00${i}
      elif [ $i -lt 1000 ]; then
         INDEX=0${i}
      else
         INDEX=${i}
      fi
      
      GetURL "${LINE_URL}" "${LINE_DATE}" ${INDEX}
   fi
done
