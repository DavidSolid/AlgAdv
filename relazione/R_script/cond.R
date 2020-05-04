prim_time = read.table("prim_time.txt", header = FALSE, sep = ",", dec = ".")
union_time = read.table("union_time.txt", header = FALSE, sep = ",", dec = ".")

time = read.table("time.txt", header = TRUE, sep = ",", dec = ".")
weight_time = read.table("weight_over_time.txt", header = TRUE, sep = ",", dec = ".")

time$NODES = weight_time$NODES
time$PRIM = prim_time$V1
time$KRUSKAL.UNION = union_time$V1


me <- data.frame(time$NODES, time$PRIM, time$KRUSKAL.UNION, time$KRUSKAL.DFS, time$KRUSKAL.BFS)
colnames(me)  <- c("NODES", "PRIM", "UNION-FIND", "DFS", "BFS")
me <- aggregate(.~NODES, data = me, mean)



options(scipen=999)
plot(x = me$NODES, y = me$BFS, log = "xy", type = "l", col= "blue", ylab = "TEMPO DI ESECUZIONE (s)", xlab = "NUMERO DI NODI", main = "CONFRONTO TEMPI MEDI DEGLI ALGORITMI PER NUMERO DI NODI", lty = 1, lwd = 2)
lines(x = me$NODES, y = me$`UNION-FIND`, col= "green", lty = 1, lwd = 2)
lines(x = me$NODES, y = me$PRIM,col="red", lty = 1, lwd = 2)
lines(x = me$NODES, y = me$DFS,col="violet", lty = 1, lwd = 2)

points(x = me$NODES, y = me$DFS, pch= 15, col="violet", cex=0.85)
points(x = me$NODES, y = me$BFS, pch= 16, col="blue", cex=0.85)
points(x = me$NODES, y = me$`UNION-FIND`, pch= 17, col="green", cex=0.85)
points(x = me$NODES, y = me$PRIM, pch= 18, col="red", cex=0.85)
legend(legend=c("BFS", "DFS", "UNION-FIND", "PRIM"), col=c("blue", "violet", "green", "red"), title="Algoritmo", text.font=4, "topleft", lty= 1, lwd = 2)

plot(x = me$NODES, y = me$BFS, log = "x", type = "l", col= "blue", ylab = "TEMPO DI ESECUZIONE (s)", xlab = "NUMERO DI NODI", main = "CONFRONTO TEMPI MEDI KRUSKAL DFS / BFS", lty = 1, lwd = 2)
lines(x = me$NODES, y = me$DFS,col="violet", lty = 1, lwd = 2)
points(x = me$NODES, y = me$DFS, pch= 15, col="violet", cex=0.85)
points(x = me$NODES, y = me$BFS, pch= 16, col="blue", cex=0.85)
legend(legend=c("BFS", "DFS"),
       col=c("blue", "violet"), title="Algoritmo", text.font=4, "topleft", lty= 1, lwd = 2)

plot(x = me$NODES, y = me$PRIM, log = "x", type = "l", col= "red", ylab = "TEMPO DI ESECUZIONE (s)", xlab = "NUMERO DI NODI", main = "CONFRONTO TEMPI MEDI PRIM / UNION-FIND", lty = 1, lwd = 2)
lines(x = me$NODES, y = me$`UNION-FIND`,col="green", lty = 1, lwd = 2)
points(x = me$NODES, y = me$`UNION-FIND`, pch= 17, col="green", cex=0.85)
points(x = me$NODES, y = me$PRIM, pch= 18, col="red", cex=0.85)
legend(legend=c("UNION-FIND", "PRIM"),
       col=c("green", "red"), title="Algoritmo", text.font=4, "topleft", lty= 1, lwd = 2)

total_cycle <- data.frame(sum(time$PRIM), sum(time$KRUSKAL.UNION),sum(time$KRUSKAL.DFS),sum(time$KRUSKAL.BFS))
colnames(total_cycle) <- c("PRIM", "UNION-FIND", "DFS", "BFS")

time_weight <- data.frame(time$GRAPH, time$PRIM, time$KRUSKAL.UNION, time$KRUSKAL.DFS, time$KRUSKAL.BFS, weight_time$KRUSKAL.UNION)
write.csv(x = time_weight, file = "final_time.csv", row.names = FALSE, quote = FALSE)

write.csv(x = me, file = "final_mean.csv", row.names = FALSE, quote = FALSE)