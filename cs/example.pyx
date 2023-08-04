# 引入必要的 Python 模块和函数
import networkx as nx

# 定义函数，计算 k-2 核组件个数
def countK2CoreComponents(adjacencyMatrix, k):
    # 创建图对象
    graph = nx.Graph(adjacencyMatrix)

    # 调用 NetworkX 函数计算 k-2 核组件
    k2_core = nx.k_core(graph, k-2)

    # 统计 k-2 核组件个数
    componentCount = nx.number_connected_components(k2_core)

    # 返回 k-2 核组件个数
    return componentCount
