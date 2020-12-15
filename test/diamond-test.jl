using LinearAlgebra
using Random
include("graph-related.jl")
function diamondVsCircular(X, sample_size=1e6)
    # return the probability of min cost (diamond extra edge, circular)
    diamond_route_count  = 0
    circular_route_count = 0

    for i = 1:sample_size
        generateWeights(X)
        if usingDividerClosedWalk(X) < sum(X[1:end - 1])
            diamond_route_count += 1
        else
            circular_route_count += 1
        end
    end

    return (diamond_route_count / sample_size,
        circular_route_count / sample_size)
end



for i in 5:10
    X = zeros(i)
    println(diamondVsCircular(X))
end
