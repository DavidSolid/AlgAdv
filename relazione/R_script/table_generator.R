time = read.table("time.txt", header = TRUE, sep = ",", dec = ".")
res = read.table("res.txt", header = TRUE, sep = ",", dec = ".")
weight = read.table("weight.txt", header = TRUE, sep = ",", dec = ".")
weight_time = read.table("weight_over_time.txt", header = TRUE, sep = ",", dec = ".")
time$NODES = weight_time$NODES
time$MST.WEIGHT = weight$WEIGHT

time_mean <- data.frame(0,time$NODES, time$PRIM, time$KRUSKAL.UNION, time$KRUSKAL.DFS, time$KRUSKAL.BFS)
time_mean <- aggregate(.~time.NODES, data = time_mean, mean)
colnames(time_mean) <- c("NODES", "GRAPHS", "PRIM", "KRUSKAL.UNION", "KRUSKAL.DFS", "KRUSKAL:BFS")
time_mean <- time_mean[, c(2,1,3,4,5,6)]
write.csv(x = time_mean, file = "time_mean3.csv", row.names = FALSE, quote = FALSE)
for (i in 1:nrow(time_mean)) {
  n <- (4*(i-1))+1
  t <- n:(n+3)
  time_mean$GRAPHS[i] <- paste(t, collapse = ", ")
} 

library(gplots)

png("PRIM_MEDIA.png", width = 927, height = 396)
plotmeans(PRIM ~ NODES, data = time, frame = FALSE, mean.labels = FALSE, xlab = "Numero di Nodi", ylab = "Tempo di esecuzione", col = "red", ccol = "black")
dev.off()

png("K_DFS_MEDIA.png", width = 927, height = 396)
plotmeans(KRUSKAL.DFS ~ NODES, data = time, frame = FALSE, mean.labels = FALSE, xlab = "Numero di Nodi", ylab = "Tempo di esecuzione", col = "red", ccol = "black")
dev.off()

png("K_UNION_MEDIA.png", width = 927, height = 396)
plotmeans(KRUSKAL.UNION ~ NODES, data = time, frame = FALSE, mean.labels = FALSE, xlab = "Numero di Nodi", ylab = "Tempo di esecuzione", col = "red", ccol = "black")
dev.off()

png("K_BFS_MEDIA.png", width = 927, height = 396)
plotmeans(KRUSKAL.BFS ~ NODES, data = time, frame = FALSE, mean.labels = FALSE, xlab = "Numero di Nodi", ylab = "Tempo di esecuzione", col = "red", ccol = "black")
dev.off()


options(scipen=999)

png("PRIM_NORMALE.png", width = 927, height = 396)
plot(x = time_mean$NODES, y = time_mean$PRIM , type = "l", xlab = "Numero di nodi", ylab = "Tempo di esecuzione", main = "Prim")
points(time_mean$NODES, time_mean$PRIM, pch='o', col='red')
dev.off()

png("K_DFS_NORMALE.png", width = 927, height = 396)
plot(x = time_mean$NODES, y = time_mean$KRUSKAL.DFS , type = "l", xlab = "Numero di nodi", ylab = "Tempo di esecuzione", main = "KRUSKAL DFS")
points(time_mean$NODES, time_mean$KRUSKAL.DFS, pch='o', col='red')
dev.off()

png("K_UNION_NORMALE.png", width = 927, height = 396)
plot(x = time_mean$NODES, y = time_mean$KRUSKAL.UNION , type = "l", xlab = "Numero di nodi", ylab = "Tempo di esecuzione", main = "KRUSKAL UNION-FIND")
points(time_mean$NODES, time_mean$KRUSKAL.UNION, pch='o', col='red')
dev.off()

png("K_BFS_NORMALE.png", width = 927, height = 396)
plot(x = time_mean$NODES, y = time_mean$KRUSKAL.BFS , type = "l", xlab = "Numero di nodi", ylab = "Tempo di esecuzione", main = "KRSUKAL BFS")
points(time_mean$NODES, time_mean$KRUSKAL.BFS, pch='o', col='red')
dev.off()


write.csv(x = time[, c(1,2,3,4,5,7)], file = "time_tab2.csv", row.names = FALSE, quote = FALSE)
write.csv(x = res, file = "res_tab2.csv", row.names = FALSE, quote = FALSE)
write.csv(x = weight, file = "weight_tab2.csv", row.names = FALSE, quote = FALSE)
write.csv(x = time_mean, file = "time_mean2.csv", row.names = FALSE, quote = FALSE)

library(xtable)

print(xtable(time[, c(1,2,3,4,5,7)]), type="latex", file="time.tex",include.rownames = FALSE)

total_cycle <- data.frame(sum(time$PRIM), sum(time$KRUSKAL.UNION),sum(time$KRUSKAL.DFS),sum(time$KRUSKAL.BFS))
colnames(time_mean) <- c("PRIM", "K. UNION-FIND", "K. DFS", "K. BFS")
#total_cycle <- rowSums(total_cycle)

me <- data.frame(time$NODES, time$PRIM, time$KRUSKAL.UNION, time$KRUSKAL.DFS, time$KRUSKAL.BFS)
colnames(me)  <- c("NODES", "PRIM", "UNION-FIND", "DFS", "BFS")
me <- aggregate(.~NODES, data = me, mean)
options(scipen=999)
plot(x = me$NODES, y = me$PRIM, log = "x", type = "l", col= "red")
#points(x = me$NODES, y = me$PRIM, type = )
lines(x = me$NODES, y = me$`UNION-FIND`,col="green")


plot(x = me$NODES, y = me$`UNION-FIND`, log = "x", type = "l", col= "green", ylab = "TEMPO DI ESECUZIONE", xlab = "NUMERO DI NODI", main = "CONFRONTO PRIM / UNION-FIND", lty = "dotted")
lines(x = me$NODES, y = me$PRIM,col="red", lty = "dashed", lwd = 2)
points(x = me$NODES, y = me$PRIM, pch= 0, col="red", lwd = 2)
points(x = me$NODES, y = me$`UNION-FIND`, pch= 1, col="green")
legend(legend=c("Prim", "Union-Find"),
       col=c("red", "green"), title="Algoritmo", text.font=4, "topleft", lty= 2:3, lwd = 2)

plot(x = me$NODES, y = me$BFS, log = "x", type = "l", col= "blue", ylab = "TEMPO DI ESECUZIONE", xlab = "NUMERO DI NODI", main = "CONFRONTO KRUSKAL DFS / BFS", lty = "dotted")
lines(x = me$NODES, y = me$DFS,col="orange", lty = "dashed", lwd = 2)
points(x = me$NODES, y = me$DFS, pch= 0, col="orange", lwd = 2)
points(x = me$NODES, y = me$BFS, pch= 1, col="blue")
legend(legend=c("DFS", "BFS"),
       col=c("orange", "blue"), title="Algoritmo", text.font=4, "topleft", lty= 2:3, lwd = 2)



