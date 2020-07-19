#!/usr/bin/ruby

# produces a Newick format tree given a maketree generated dot format tree
# looks for a label "humanMito" to use as root
TREEFILE='/home/rudi/var/covid-exp/intermediate/treefile.dot'

def doDFS(labels, neighbors, fromWhere, doneNodes)
	cur = fromWhere
	return if doneNodes[fromWhere]
	doneNodes[cur] = true
	str = "("
	strList = [ ]
	neighbors[cur].each do |n|
		unless doneNodes[n]
			strList.append(doDFS(labels, neighbors, n, doneNodes))
		end
	end
	str += strList.join(',')
	str += ")"
	if str.size == 2
		str = ''
	end
	label = labels[fromWhere]
	if label && !label.empty?
		str += "#{labels[fromWhere]}"
	end
	return str
end
Dir.chdir('/home/rudi/var/covid-exp/intermediate')
file = File.open(TREEFILE, "r");
lines = file.readlines
labels = { }
neighbors = { }
humanMitoIndex = nil
lines.each { |line|
#	puts "got line: #{line}"
	if line =~ /^(\d+)\s+\[label="([^"]*)"/
		num = $1.to_i
		label = $2.to_s
		if label.size > 0 && num < 120
#			puts "label #{num} = #{label}"
			labels[num] = label
			if label == "humanMito"
				humanMitoIndex = num
			end
		end
	end
	if line =~ /^(\d+) -- (\d+) \[weight/;
		a = $1.to_i
		b = $2.to_i
#		puts "EDGE #{a} -- #{b}"
		neighbors[a] ||= []
		neighbors[a].append(b)
		neighbors[b] ||= []
		neighbors[b].append(a)
	end
}
doneNodes = { }
treestr = doDFS(labels, neighbors, humanMitoIndex, doneNodes)
puts treestr + ';'
exit(0)
