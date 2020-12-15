using LinearAlgebra
using Random

include("graph-related.jl")

function repeatedVsCircular(X, sample_size=1e5)
    # return the probability of min cost (repeated, circular)
    repeated_route_count  = 0
    circular_route_count = 0

    for i = 1:sample_size
        generateWeights(X)
        if minRepeatedClosedWalk(X) < sum(X)
            repeated_route_count += 1
        else
            circular_route_count += 1
        end
    end

    return (repeated_route_count / sample_size,
        circular_route_count / sample_size)
end

for i in 3:10
    X = zeros(i)
    println(repeatedVsCircular(X))
end
