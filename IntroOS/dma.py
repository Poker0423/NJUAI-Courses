class DMA:
    def __init__(self, size):
        # 假设初始化时空间中每个地址都存储一个 # 符号
        self.heap = ['#'] * size
        # 你可以在这里额外定义需要的数据结构
        self.allocations = {}  # {id: {'start': start, 'size': size, 'value': value}}
        self.free_spaces = [(0, size)]  # 使用列表维护空闲空间
        self.cnt = 0


    # 你需要实现以下三个 API
    def malloc(self, id: int, size: int, value: list) -> bool:
        strategy = self._choose_strategy(size)
        index, start, free_size = self._find_free_space(size, strategy)
        if start is None and sum(free_size for _, free_size in self.free_spaces) >= size:
            self.compact()
            self.cnt = 0
            index, start, free_size = self._find_free_space(size, strategy)

        if start is None:
            return False
     # 分配内存
        self.heap[start:start + size] = value
        self.allocations[id] = {'start': start, 'size': size, 'value': value}
    # 更新空闲空间
        if free_size == size:
            del self.free_spaces[index]
        else:
            self.free_spaces[index] = (start + size, free_size - size)
            
        if self.cnt >=3 :
            self.compact()
            self.cnt = 0
        else:
            self.cnt+=1
            
        return True


    def free(self, id: int) -> bool:
        if id not in self.allocations:
            return False

        allocation = self.allocations.pop(id)
        start = allocation['start']
        size = allocation['size']
        # 将内存标记为空闲
        self.heap[start:start + size] = ['#'] * size
        # 添加新的空闲块并尝试合并空闲块
        self.free_spaces.append((start, size))
        self._merge_free_spaces()
        #self.compact()
        return True

    def data(self) -> dict:
        return self.allocations
        
        
        
    def _choose_strategy(self, size):
    # 根据请求大小选择策略
        heap_length = len(self.heap)
        if size > heap_length // 2:
            return 'worst_fit'
        elif size < heap_length // 10:
            return 'best_fit'
        else:
            return 'first_fit'
        
    def _find_free_space(self, size, strategy='first_fit'):
        if strategy == 'best_fit':
            best_fit = None
            best_index = None
            for index, (start, free_size) in enumerate(self.free_spaces):
                if free_size >= size and (best_fit is None or free_size < best_fit[1]):
                    best_fit = (start, free_size)
                    best_index = index
            if best_fit:
                return best_index, best_fit[0], best_fit[1]
        elif strategy == 'worst_fit':
            worst_fit = None
            worst_index = None
            for index, (start, free_size) in enumerate(self.free_spaces):
                if free_size >= size and (worst_fit is None or free_size > worst_fit[1]):
                    worst_fit = (start, free_size)
                    worst_index = index
            if worst_fit:
                return worst_index, worst_fit[0], worst_fit[1]
        else:  # 默认使用 First Fit
            for index, (start, free_size) in enumerate(self.free_spaces):
                if free_size >= size:
                    return index, start, free_size
        return None, None, None



    def _merge_free_spaces(self):
    # 合并相邻空闲块
        self.free_spaces = sorted(self.free_spaces)  #按起始地址排序
        merged = []
        prev_start, prev_size = self.free_spaces[0] 
        for start, size in self.free_spaces[1:]:
            if prev_start + prev_size == start:
                prev_size += size
            else:
                merged.append((prev_start, prev_size))
                prev_start, prev_size = start, size
        merged.append((prev_start, prev_size))
        self.free_spaces = merged
        self.free_spaces = sorted(self.free_spaces, key=lambda x: x[0]) #2


    # 除了上述 API 外，你可以额外定义必要的辅助函数
    # 例如，通过调用 compact 来对内存空间进行碎片整理
    def compact(self) -> None:
        # 进行内存碎片整理
        new_heap = ['#'] * len(self.heap)
        new_allocations = {}
        current_position = 0
        sorted_allocations = sorted(self.allocations.items(), key=lambda x: x[1]['start'])
        # 移动所有分配的块并更新起始位置
        for id, allocation in sorted_allocations:
            size = allocation['size']
            new_heap[current_position:current_position + size] = allocation['value']
            new_allocations[id] = {'start': current_position, 'size': size, 'value': allocation['value']}
            current_position += size
        self.heap = new_heap
        self.allocations = new_allocations
        self.free_spaces = [(current_position, len(self.heap) - current_position)]
