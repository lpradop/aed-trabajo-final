function generateWeights(X)
    for i in 1:length(X)
        X[i] = rand(10:80)
    end
end

function minRepeatedClosedWalk(X)
    # for cycle graph,
    # repeating at least one edge
    return 2 * (sum(X) - maximum(X))
end

function minClosedWalk(X)
    return min(minRepeatedClosedWalk(X), sum(X))
end

function usingDividerClosedWalk(X)
    return sum(X) + minimum(X[1:end - 1]) - maximum(X[1:end - 1])
end