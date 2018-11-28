PATHTOLIB=~/mydir/projects/libft
PATHTOBENCH=~/mydir/projects/lib_bench
cd ${PATHTOLIB}
FCTS=`ls ft_*`
FCTSBENCH=`
for fct in ${FCTS}
do
	find ${PATHTOLIB} -name $fct -print
	find ${PATHTOBENCH} -name $fct -print
done`
cat ${FCTSBENCH} | less

