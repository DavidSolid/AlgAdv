time = read.table("time.txt", header = TRUE, sep = ",", dec = ".")
weight_time = read.table("weight_over_time.txt", header = TRUE, sep = ",", dec = ".")
time$NODES = weight_time$NODES
me <- data.frame(time$NODES, time$PRIM, time$KRUSKAL.UNION, time$KRUSKAL.DFS, time$KRUSKAL.BFS)
colnames(me)  <- c("NODES", "PRIM", "UNION-FIND", "DFS", "BFS")
me <- aggregate(.~NODES, data = me, mean)

options(scipen=999)
plot(x = me$NODES, y = me$BFS, log = "xy", type = "l", col= "blue", ylab = "TEMPO DI ESECUZIONE", xlab = "NUMERO DI NODI", main = "CONFRONTO KRUSKAL DFS / BFS", lty = 1, lwd = 2)
lines(x = me$NODES, y = me$`UNION-FIND`, col= "green", lty = 1, lwd = 2)
lines(x = me$NODES, y = me$PRIM,col="red", lty = 1, lwd = 2)




lines(x = me$NODES, y = me$DFS,col="orange", lty = 1, lwd = 2)
points(x = me$NODES, y = me$DFS, pch= 0, col="orange", cex.lab=0.75)
points(x = me$NODES, y = me$BFS, pch= 1, col="blue", cex.lab=0.75)
points(x = me$NODES, y = me$`UNION-FIND`, pch= 2, col="green", cex.lab=0.75)
points(x = me$NODES, y = me$PRIM, pch= 6, col="red", cex.lab=0.75)
#legend(legend=c("DFS", "BFS"), col=c("orange", "blue"), title="Algoritmo", text.font=4, "topleft", lty= 2:3, lwd = 2)