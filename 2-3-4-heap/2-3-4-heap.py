'''
Created on Sep 14, 2013

@author: duozhao
'''
class Node234(object):
    def __init__ (self):
        self.small = 99999
        self.parent = None
        self.children_list = []
    
    def getMinLeaf(self):        
        for node in self.children_list:
            if node.small == self.small:
                return node.getMinLeaf()
    
    def decreaseSmall(self, k):
        if k < self.small:
            self.small = k
            if self.parent:
                self.parent.decreaseSmall(k)
    
    def insert(self, x): 
        key = x.key     
        if self.branchFactor == 4: 
            left, right, p = self.splitFull()
            left.insert(x) # why left? 
        else:
            self.leastFullChild.insert(x)
    
    def fix_underload(self):
        parent = self.parent
        if parent and self.branchFactor == 1:
            if parent.branchFactor == 1:
                parent.takeCustodyOf(self.children_list)
                parent.height -= 1
                self.detach()
            else:
                sibling = self.leastFullSibling
                if sibling.branchFactor < 4:
                    sibling.acquisite(self)
                    parent.fix_underload()
                else:
                    left, right, p = sibling.splitFull()
                    left.acquisite(self)
                    self.detach()
                
            
    def takeCustodyOf(self, children_list):
        for child in children_list:
            self.children_list.append(child)
            child.parent = self
            if child.small < self.small:
                self.small = child.small
 
    def acquisite(self, y): # y is another sibling node
        if self.parent == y.parent and self != y:
            self.takeCustodyOf(y.children_list)
            y.detach()
        else:
            print 'Not Silblings, Cannot acquisite'
            
    def detach(self):
        if self.parent:
            self.parent.children_list.remove(self)
        self.parent = None
        self.children_list =[]
        self.small = 99999       
    
    def splitFull(self):
        if self.branchFactor == 4:
            parent = self.parent
            new_left, new_right = Node234(), Node234()
            
            new_left.takeCustodyOf(self.children_list[0:2])
            new_right.takeCustodyOf(self.children_list[2:4])
            
            self.detach()
            
            parent.takeCustodyOf([new_left, new_right])
            return new_left, new_right, parent
        else:
            print "Not Full to Split"
        
    def printChildren(self):
        print [c.small for c in self.children_list]
        
    def walk(self, level):
        print '\t' * level, self.small
        for child in self.children_list:
            child.walk(level + 1)
    
    @property
    def branchFactor(self):
        return len(self.children_list)
    
    @property
    def leastFullChild (self):
        n_min = 6
        child_min = None
        for child in self.children_list:
            n = child.branchFactor
            if n < n_min:
                n_min = n 
                child_min = child
        return child_min
    
    @property
    def leastFullSibling(self):
        n_min = 6
        sibling_min = None
        parent = self.parent
        for sibling in parent.children_list:
            if sibling != self:
                n = sibling.branchFactor
                if n < n_min:
                    n_min = n
                    sibling_min = sibling
        return sibling_min


class Left234(Node234):
    def __init__ (self, key):
        super(Left234, self).__init__()
        self.small = key
        self.key = key
    
    def getMinLeaf(self):
        return self
    
    def decreaseKey(self, k):
        if k < self.small:
            self.key = k
            super(Left234, self).decreaseSmall(k)
        else:
            print 'Key increases'
    
    def insert(self,x):
        self.parent.children_list.append(x)
        x.parent = self.parent

    
    def delete(self):
        key = self.key
        parent = self.parent
        parent.children_list.remove(self)
        cursor = parent
        while cursor and (cursor.small == key) :
            cursor.small = min([node.small for node in cursor.children_list])
            cursor = cursor.parent
        
        parent.fix_underload()
        
           
class Root234(Node234):
    def __init__ (self):
        super(Root234, self).__init__()
        self.parent = None
        self.height = 0
    
    def insert(self, x):
        key = x.key
        if self.height == 0:
            self.small = key
            self.children_list.append(x)
            x.parent = self
            self.height += 1
            return self
        
        elif self.branchFactor == 4: 
            left, right, new_root = self.splitFull()
            left.insert(x) #
            return new_root
            
        else:
            child_to_insert = self.leastFullChild
            child_to_insert.insert(x)
            return self
    
    def rootToRegular(self):
        regularNode = Node234()
        regularNode.small = self.small
        regularNode.children_list = self.children_list
        self.detach()
        return regularNode
    
    def splitFull(self):
        if self.branchFactor == 4:
            newRoot = Root234()
            newRoot.height = self.height + 1
            newRoot.takeCustodyOf([self])
            return super(Root234, self).splitFull()
    
    def leastFullSibling(self):
        return None
    
    def extract_min(self):
        minLeaf = self.getMinLeaf()
        minLeaf.delete()
        pass
    
    def union(self, guestRoot):
        if guestRoot.height == 0:
            return self
        
        elif self.height == guestRoot.height:
            newRoot = Root234()
            newRoot.height = self.height + 1
            newRoot.takeCustodyOf([self.rootToRegular(), 
                                   guestRoot.rootToRegular()])           
            return newRoot
        
        elif self.height > guestRoot.height:
            newRoot = self
            navShadow = self
            cursor = guestRoot
            
            top_navShadow = self.height
            bottom_navShadow = guestRoot.height
            
            if cursor.branchFactor == 1:
                cursor = guestRoot.children_list[0]
                bottom_navShadow -= 1
                guestRoot.detach()
            else:
                cursor = cursor.rootToRegular()
                
            for h in xrange(top_navShadow, bottom_navShadow, -1):
                if navShadow.branchFactor == 4:
                    left, right, p = navShadow.splitFull()
                    navShadow = left
                    if h == top_navShadow:
                        newRoot = p       
                if h != bottom_navShadow + 1:
                    navShadow = navShadow.leastFullChild
            navShadow.takeCustodyOf([cursor])
            return newRoot
        
        else:
            return guestRoot.union(self)
            

if __name__ == '__main__':
    print 'hello, world'
    node_list = [Left234(val) for val in range(10,24)]
    node_list2 =  [Left234(val) for val in range(500,504)] 
    
    leaf = Node234()
    leaf.key = 20
    leaf.small = 20
    
    root = Root234()
    root2 = Root234()
    for node in node_list:
        root = root.insert(node)
    for node in node_list2:
        root2 = root2.insert(node)
    print "------------"
    node_list[6].decreaseKey(1)
    root.walk(0)
#     root.children_list[1].children_list.append(leaf)
#     leaf.parent = root.children_list[1]
    root.children_list.remove( root.children_list[0])
    root.small = 12
    node_list[5].decreaseKey(1)
    print "--------add----"
    root.walk(0)
    print "---------add---"
    root2.walk(0)
    
    
    print "-------extract min -----"
    root.extract_min()
    root.walk(0)
    print "------------"
    print "union"
    root3 = root.union(root2)
    root3.walk(0)
    print "------------"
    
